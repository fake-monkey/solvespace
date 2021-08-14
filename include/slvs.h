/*-----------------------------------------------------------------------------
 * Data structures and prototypes for slvs.lib, a geometric constraint solver.
 *
 * See the comments in this file, the accompanying sample code that uses
 * this library, and the accompanying documentation (DOC.txt).
 *
 * Copyright 2009-2013 Jonathan Westhues.
 *---------------------------------------------------------------------------*/

#ifndef __SLVS_H
#define __SLVS_H

#ifdef WIN32
#   ifdef EXPORT_DLL
#       define DLL __declspec( dllexport )
#   else
#       define DLL __declspec( dllimport )
#   endif
#else
#   define DLL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
typedef unsigned __int32 uint32_t;
#else
#include <stdint.h>
#endif

typedef uint32_t Slvs_hParam;
typedef uint32_t Slvs_hEntity;
typedef uint32_t Slvs_hConstraint;
typedef uint32_t Slvs_hGroup;

/* To obtain the 3d (not projected into a workplane) of a constraint or
 * an entity, specify this instead of the workplane. */
#define SLVS_FREE_IN_3D         0


typedef struct {
    Slvs_hParam     h;
    Slvs_hGroup     group;
    double          val;
} Slvs_Param;

typedef enum {
    SLVS_E_POINT_IN_3D            = 2000,
    SLVS_E_POINT_IN_2D            = 2001,
    SLVS_E_POINT_N_TRANS          = 2010,
    SLVS_E_POINT_N_ROT_TRANS      = 2011,
    SLVS_E_POINT_N_COPY           = 2012,
    SLVS_E_POINT_N_ROT_AA         = 2013,
    SLVS_E_POINT_N_ROT_AXIS_TRANS = 2014,

    SLVS_E_NORMAL_IN_3D    = 3000,
    SLVS_E_NORMAL_IN_2D    = 3001,
    SLVS_E_NORMAL_N_COPY   = 3010,
    SLVS_E_NORMAL_N_ROT    = 3011,
    SLVS_E_NORMAL_N_ROT_AA = 3012,

    SLVS_E_DISTANCE        = 4000,
    SLVS_E_DISTANCE_N_COPY = 4001,

    SLVS_E_FACE_NORMAL_PT        = 5000,
    SLVS_E_FACE_XPROD            = 5001,
    SLVS_E_FACE_N_ROT_TRANS      = 5002,
    SLVS_E_FACE_N_TRANS          = 5003,
    SLVS_E_FACE_N_ROT_AA         = 5004,
    SLVS_E_FACE_ROT_NORMAL_PT    = 5005,
    SLVS_E_FACE_N_ROT_AXIS_TRANS = 5006,

    SLVS_E_WORKPLANE      = 10000,
    SLVS_E_LINE_SEGMENT   = 11000,
    SLVS_E_CUBIC          = 12000,
    SLVS_E_CUBIC_PERIODIC = 12001,
    SLVS_E_CIRCLE         = 13000,
    SLVS_E_ARC_OF_CIRCLE  = 14000,
    SLVS_E_TTF_TEXT       = 15000,
    SLVS_E_IMAGE          = 16000,
} Slvs_EntityType;

typedef struct {
    Slvs_hEntity    h;
    Slvs_hGroup     group;

    Slvs_EntityType type;

    Slvs_hEntity    wrkpl;
    Slvs_hEntity    point[4];
    Slvs_hEntity    normal;
    Slvs_hEntity    distance;

    Slvs_hParam     param[4];

    int             construction;
} Slvs_Entity;

typedef enum {
    SLVS_C_POINTS_COINCIDENT   = 20,
    SLVS_C_PT_PT_DISTANCE      = 30,
    SLVS_C_PT_PLANE_DISTANCE   = 31,
    SLVS_C_PT_LINE_DISTANCE    = 32,
    SLVS_C_PT_FACE_DISTANCE    = 33,
    SLVS_C_PROJ_PT_DISTANCE    = 34,
    SLVS_C_PT_IN_PLANE         = 41,
    SLVS_C_PT_ON_LINE          = 42,
    SLVS_C_PT_ON_FACE          = 43,
    SLVS_C_EQUAL_LENGTH_LINES  = 50,
    SLVS_C_LENGTH_RATIO        = 51,
    SLVS_C_EQ_LEN_PT_LINE_D    = 52,
    SLVS_C_EQ_PT_LN_DISTANCES  = 53,
    SLVS_C_EQUAL_ANGLE         = 54,
    SLVS_C_EQUAL_LINE_ARC_LEN  = 55,
    SLVS_C_LENGTH_DIFFERENCE   = 56,
    SLVS_C_SYMMETRIC           = 60,
    SLVS_C_SYMMETRIC_HORIZ     = 61,
    SLVS_C_SYMMETRIC_VERT      = 62,
    SLVS_C_SYMMETRIC_LINE      = 63,
    SLVS_C_AT_MIDPOINT         = 70,
    SLVS_C_HORIZONTAL          = 80,
    SLVS_C_VERTICAL            = 81,
    SLVS_C_DIAMETER            = 90,
    SLVS_C_PT_ON_CIRCLE        = 100,
    SLVS_C_SAME_ORIENTATION    = 110,
    SLVS_C_ANGLE               = 120,
    SLVS_C_PARALLEL            = 121,
    SLVS_C_PERPENDICULAR       = 122,
    SLVS_C_ARC_LINE_TANGENT    = 123,
    SLVS_C_CUBIC_LINE_TANGENT  = 124,
    SLVS_C_CURVE_CURVE_TANGENT = 125,
    SLVS_C_EQUAL_RADIUS        = 130,
    SLVS_C_WHERE_DRAGGED       = 200,

    SLVS_C_COMMENT = 1000,
} Slvs_ConstraintType;

typedef struct {
    Slvs_hConstraint    h;
    Slvs_hGroup         group;

    Slvs_ConstraintType type;

    Slvs_hEntity        wrkpl;

    double              valA;
    Slvs_hEntity        ptA;
    Slvs_hEntity        ptB;
    Slvs_hEntity        entityA;
    Slvs_hEntity        entityB;
    Slvs_hEntity        entityC;
    Slvs_hEntity        entityD;

    int                 other;
    int                 other2;

    char                *name;
} Slvs_Constraint;


typedef struct {
    /*** INPUT VARIABLES
     *
     * Here, we specify the parameters and their initial values, the entities,
     * and the constraints. For example, param[] points to the array of
     * parameters, which has length params, so that the last valid element
     * is param[params-1].
     *
     * param[] is actually an in/out variable; if the solver is successful,
     * then the new values (that satisfy the constraints) are written to it. */
    Slvs_Param          *param;
    int                 params;
    Slvs_Entity         *entity;
    int                 entities;
    Slvs_Constraint     *constraint;
    int                 constraints;

    /* If a parameter corresponds to a point (distance, normal, etc.) being
     * dragged, then specify it here. This will cause the solver to favor
     * that parameter, and attempt to change it as little as possible even
     * if that requires it to change other parameters more.
     *
     * Unused members of this array should be set to zero. */
    Slvs_hParam         dragged[4];

    /* If the solver fails, then it can determine which constraints are
     * causing the problem. But this is a relatively slow process (for
     * a system with n constraints, about n times as long as just solving).
     * If calculateFaileds is true, then the solver will do so, otherwise
     * not. */
    int                 calculateFaileds;

    /*** OUTPUT VARIABLES
     *
     * If the solver fails, then it can report which constraints are causing
     * the problem. The caller should allocate the array failed[], and pass
     * its size in faileds.
     *
     * The solver will set faileds equal to the number of problematic
     * constraints, and write their Slvs_hConstraints into failed[]. To
     * ensure that there is sufficient space for any possible set of
     * failing constraints, faileds should be greater than or equal to
     * constraints. */
    Slvs_hConstraint    *failed;
    int                 faileds;

    /* The solver indicates the number of unconstrained degrees of freedom. */
    int                 dof;

    /* The solver indicates whether the solution succeeded. */
#define SLVS_RESULT_OKAY                0
#define SLVS_RESULT_INCONSISTENT        1
#define SLVS_RESULT_DIDNT_CONVERGE      2
#define SLVS_RESULT_TOO_MANY_UNKNOWNS   3
    int                 result;
} Slvs_System;

DLL void Slvs_Solve(Slvs_System *sys, Slvs_hGroup hg);


/* Our base coordinate system has basis vectors
 *     (1, 0, 0)  (0, 1, 0)  (0, 0, 1)
 * A unit quaternion defines a rotation to a new coordinate system with
 * basis vectors
 *         U          V          N
 * which these functions compute from the quaternion. */
DLL void Slvs_QuaternionU(double qw, double qx, double qy, double qz,
                             double *x, double *y, double *z);
DLL void Slvs_QuaternionV(double qw, double qx, double qy, double qz,
                             double *x, double *y, double *z);
DLL void Slvs_QuaternionN(double qw, double qx, double qy, double qz,
                             double *x, double *y, double *z);

/* Similarly, compute a unit quaternion in terms of two basis vectors. */
DLL void Slvs_MakeQuaternion(double ux, double uy, double uz,
                             double vx, double vy, double vz,
                             double *qw, double *qx, double *qy, double *qz);


/*-------------------------------------
 * These are just convenience functions, to save you the trouble of filling
 * out the structures by hand. The code is included in the header file to
 * let the compiler inline them if possible. */

static inline Slvs_Param Slvs_MakeParam(Slvs_hParam h, Slvs_hGroup group, double val)
{
    Slvs_Param r;
    r.h = h;
    r.group = group;
    r.val = val;
    return r;
}
static inline Slvs_Entity Slvs_MakePoint2d(Slvs_hEntity h, Slvs_hGroup group,
                                           Slvs_hEntity wrkpl,
                                           Slvs_hParam u, Slvs_hParam v)
{
    Slvs_Entity r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type  = SLVS_E_POINT_IN_2D;
    r.wrkpl = wrkpl;
    r.param[0] = u;
    r.param[1] = v;
    return r;
}
static inline Slvs_Entity Slvs_MakePoint3d(Slvs_hEntity h, Slvs_hGroup group,
                                           Slvs_hParam x, Slvs_hParam y, Slvs_hParam z)
{
    Slvs_Entity r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type  = SLVS_E_POINT_IN_3D;
    r.wrkpl = SLVS_FREE_IN_3D;
    r.param[0] = x;
    r.param[1] = y;
    r.param[2] = z;
    return r;
}
static inline Slvs_Entity Slvs_MakeNormal3d(Slvs_hEntity h, Slvs_hGroup group,
                                            Slvs_hParam qw, Slvs_hParam qx,
                                            Slvs_hParam qy, Slvs_hParam qz)
{
    Slvs_Entity r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type  = SLVS_E_NORMAL_IN_3D;
    r.wrkpl = SLVS_FREE_IN_3D;
    r.param[0] = qw;
    r.param[1] = qx;
    r.param[2] = qy;
    r.param[3] = qz;
    return r;
}
static inline Slvs_Entity Slvs_MakeNormal2d(Slvs_hEntity h, Slvs_hGroup group,
                                            Slvs_hEntity wrkpl)
{
    Slvs_Entity r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type  = SLVS_E_NORMAL_IN_2D;
    r.wrkpl = wrkpl;
    return r;
}
static inline Slvs_Entity Slvs_MakeDistance(Slvs_hEntity h, Slvs_hGroup group,
                                            Slvs_hEntity wrkpl, Slvs_hParam d)
{
    Slvs_Entity r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type  = SLVS_E_DISTANCE;
    r.wrkpl = wrkpl;
    r.param[0] = d;
    return r;
}
static inline Slvs_Entity Slvs_MakeLineSegment(Slvs_hEntity h, Slvs_hGroup group,
                                               Slvs_hEntity wrkpl,
                                               Slvs_hEntity ptA, Slvs_hEntity ptB)
{
    Slvs_Entity r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type  = SLVS_E_LINE_SEGMENT;
    r.wrkpl = wrkpl;
    r.point[0] = ptA;
    r.point[1] = ptB;
    return r;
}
static inline Slvs_Entity Slvs_MakeCubic(Slvs_hEntity h, Slvs_hGroup group,
                                         Slvs_hEntity wrkpl,
                                         Slvs_hEntity pt0, Slvs_hEntity pt1,
                                         Slvs_hEntity pt2, Slvs_hEntity pt3)
{
    Slvs_Entity r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type  = SLVS_E_CUBIC;
    r.wrkpl = wrkpl;
    r.point[0] = pt0;
    r.point[1] = pt1;
    r.point[2] = pt2;
    r.point[3] = pt3;
    return r;
}
static inline Slvs_Entity Slvs_MakeArcOfCircle(Slvs_hEntity h, Slvs_hGroup group,
                                               Slvs_hEntity wrkpl,
                                               Slvs_hEntity normal,
                                               Slvs_hEntity center,
                                               Slvs_hEntity start, Slvs_hEntity end)
{
    Slvs_Entity r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type  = SLVS_E_ARC_OF_CIRCLE;
    r.wrkpl = wrkpl;
    r.normal = normal;
    r.point[0] = center;
    r.point[1] = start;
    r.point[2] = end;
    return r;
}
static inline Slvs_Entity Slvs_MakeCircle(Slvs_hEntity h, Slvs_hGroup group,
                                          Slvs_hEntity wrkpl,
                                          Slvs_hEntity center,
                                          Slvs_hEntity normal, Slvs_hEntity radius)
{
    Slvs_Entity r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type  = SLVS_E_CIRCLE;
    r.wrkpl = wrkpl;
    r.point[0] = center;
    r.normal = normal;
    r.distance = radius;
    return r;
}
static inline Slvs_Entity Slvs_MakeWorkplane(Slvs_hEntity h, Slvs_hGroup group,
                                             Slvs_hEntity origin, Slvs_hEntity normal)
{
    Slvs_Entity r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type  = SLVS_E_WORKPLANE;
    r.wrkpl = SLVS_FREE_IN_3D;
    r.point[0] = origin;
    r.normal = normal;
    return r;
}

static inline Slvs_Constraint Slvs_MakeConstraint(Slvs_hConstraint h,
                                                  Slvs_hGroup group,
                                                  Slvs_ConstraintType type,
                                                  Slvs_hEntity wrkpl,
                                                  double valA,
                                                  Slvs_hEntity ptA,
                                                  Slvs_hEntity ptB,
                                                  Slvs_hEntity entityA,
                                                  Slvs_hEntity entityB)
{
    Slvs_Constraint r;
    memset(&r, 0, sizeof(r));
    r.h = h;
    r.group = group;
    r.type = type;
    r.wrkpl = wrkpl;
    r.valA = valA;
    r.ptA = ptA;
    r.ptB = ptB;
    r.entityA = entityA;
    r.entityB = entityB;
    return r;
}

#ifdef __cplusplus
}
#endif

#endif
