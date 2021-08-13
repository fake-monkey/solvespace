#pragma once
#include "solvespace.h"
#include "slvs.h"
#include "SlvsFile/GetSYS.h"

#ifdef _DEBUG
#   define DebugDLL DLL
#else
#   define DebugDLL
#endif

namespace SlvsFile {
    using std::string;
class DebugDLL Exception {
public:
    Exception(const std::string &message) : _message(message) {
    }
    const string &Message() const {
        return _message;
    }

private:
    string _message;
};

class DebugDLL SlvsFileException : Exception {
public:
    SlvsFileException(const char *message)
        : Exception(message), _file(""), _line(-1), _function(""), _condition("") {
    }
    SlvsFileException(const char *file, int line, const char *function, const string &message)
        : Exception(message), _file(file), _line(line), _function(function), _condition("") {
    }
    SlvsFileException(const char *file, int line, const char *function, const char *condition,
                      const string &message)
        : Exception(message), _file(file), _line(line), _function(function), _condition(condition) {
    }
    const string &File() const {
        return _file;
    }
    const int Line() const {
        return _line;
    }
    const string &Function() const {
        return _function;
    }
    const string &Condition() const {
        return _condition;
    }

private:
    string _file;
    int _line;
    string _function;
    string _condition;
};

class DebugDLL SlvsLibClass {
public:
    ~SlvsLibClass() {
        ClearExisting();
    }
    typedef struct {
        Group g;
        Request r;
        Entity e;
        Param p;
        Constraint c;
        Style s;
    } TempSV;
    static TempSV sv;

    typedef struct {
        char type;
        const char *desc;
        char fmt;
        void *ptr;
    } SaveTable;
    static const SaveTable SAVED[];

    // Everything has been pruned, so we know there's no dangling references
    // to entities that don't exist. Before that, we mustn't try to display
    // the sketch!
    bool allConsistent;
    bool fileLoadError;

    // File load/save routines, including the additional files that get
    // loaded when we have link groups.
    FILE *fh;

    void ClearExisting();
    void LoadUsingTable(const Platform::Path &filename, char *key, char *val);
    bool LoadFromFile(const Platform::Path &filename, bool canCancel = false);
    int StrStartsWith(const char *str, const char *start);
    void GenerateSystem();
    SolveResult Solve();
    void Load(const char *filename);
    void ChangeConstraintVal(uint32_t v, double val);
    const char* GetConstraintName(uint32_t v);
    Sketch &GetSK() {
        return SK;
    }
    Param &GetSKParam(uint32_t hpv) {
        hParam hp = { hpv };
        return *SK.GetParam(hp);
    }
};

// The original definition of this structure is in file.cpp.
struct SAVEDptr {
    EntityMap &M() {
        return *((EntityMap *)this);
    }
    std::string &S() {
        return *((std::string *)this);
    }
    Platform::Path &P() {
        return *((Platform::Path *)this);
    }
    bool &b() {
        return *((bool *)this);
    }
    RgbaColor &c() {
        return *((RgbaColor *)this);
    }
    int &d() {
        return *((int *)this);
    }
    double &f() {
        return *((double *)this);
    }
    uint32_t &x() {
        return *((uint32_t *)this);
    }
};
} // namespace SlvsFile

#define SlvsFile_Error(message) \
    throw SlvsFile::SlvsFileException(__FILE__, __LINE__, __FUNCTION__, message);

#define SlvsFile_Assert(condition, message) \
    do { \
        if((condition) == false) { \
            throw SlvsFile::SlvsFileException(__FILE__, __LINE__, __FUNCTION__, #condition, \
                                              message); \
        } \
    } while(0)

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct {
        char *message;
    } SlvsFile_Exception;
    typedef enum {
        POINT_IN_3D            = 2000,
        POINT_IN_2D            = 2001,
        POINT_N_TRANS          = 2010,
        POINT_N_ROT_TRANS      = 2011,
        POINT_N_COPY           = 2012,
        POINT_N_ROT_AA         = 2013,
        POINT_N_ROT_AXIS_TRANS = 2014,

        NORMAL_IN_3D    = 3000,
        NORMAL_IN_2D    = 3001,
        NORMAL_N_COPY   = 3010,
        NORMAL_N_ROT    = 3011,
        NORMAL_N_ROT_AA = 3012,

        DISTANCE        = 4000,
        DISTANCE_N_COPY = 4001,

        FACE_NORMAL_PT        = 5000,
        FACE_XPROD            = 5001,
        FACE_N_ROT_TRANS      = 5002,
        FACE_N_TRANS          = 5003,
        FACE_N_ROT_AA         = 5004,
        FACE_ROT_NORMAL_PT    = 5005,
        FACE_N_ROT_AXIS_TRANS = 5006,

        WORKPLANE      = 10000,
        LINE_SEGMENT   = 11000,
        CUBIC          = 12000,
        CUBIC_PERIODIC = 12001,
        CIRCLE         = 13000,
        ARC_OF_CIRCLE  = 14000,
        TTF_TEXT       = 15000,
        IMAGE          = 16000
    } SlvsFile_EntityType;
    typedef enum {
        POINTS_COINCIDENT   = 20,
        PT_PT_DISTANCE      = 30,
        PT_PLANE_DISTANCE   = 31,
        PT_LINE_DISTANCE    = 32,
        PT_FACE_DISTANCE    = 33,
        PROJ_PT_DISTANCE    = 34,
        PT_IN_PLANE         = 41,
        PT_ON_LINE          = 42,
        PT_ON_FACE          = 43,
        EQUAL_LENGTH_LINES  = 50,
        LENGTH_RATIO        = 51,
        EQ_LEN_PT_LINE_D    = 52,
        EQ_PT_LN_DISTANCES  = 53,
        EQUAL_ANGLE         = 54,
        EQUAL_LINE_ARC_LEN  = 55,
        LENGTH_DIFFERENCE   = 56,
        SYMMETRIC           = 60,
        SYMMETRIC_HORIZ     = 61,
        SYMMETRIC_VERT      = 62,
        SYMMETRIC_LINE      = 63,
        AT_MIDPOINT         = 70,
        HORIZONTAL          = 80,
        VERTICAL            = 81,
        DIAMETER            = 90,
        PT_ON_CIRCLE        = 100,
        SAME_ORIENTATION    = 110,
        ANGLE               = 120,
        PARALLEL            = 121,
        PERPENDICULAR       = 122,
        ARC_LINE_TANGENT    = 123,
        CUBIC_LINE_TANGENT  = 124,
        CURVE_CURVE_TANGENT = 125,
        EQUAL_RADIUS        = 130,
        WHERE_DRAGGED       = 200,

        COMMENT = 1000
    } SlvsFile_ConstraintType;
    typedef enum {
        OKAY                     = 0,
        DIDNT_CONVERGE           = 10,
        REDUNDANT_OKAY           = 11,
        REDUNDANT_DIDNT_CONVERGE = 12,
        TOO_MANY_UNKNOWNS        = 20
    } SlvsFile_SolveResult;
    typedef struct
#ifdef __cplusplus
}
#endif
