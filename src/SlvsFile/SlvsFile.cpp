#define LIBRARY
#define EXPORT_DLL
#define VERSION_STRING "\261\262\263" "SolveSpaceREVa"
#include "solvespace.h"
#include "dsc.h"
#include <string>
#include "SlvsFile.h"
#include "GetSYS.h"

void SolveSpace::Sketch::Clear() {
    //group.Clear();
    groupOrder.Clear();
    constraint.Clear();
    request.Clear();
    style.Clear();
    entity.Clear();
    param.Clear();
}

void SolveSpace::Sketch::Empty() {
    //group.Empty();
    groupOrder.Empty();
    constraint.Empty();
    request.Empty();
    style.Empty();
    entity.Empty();
    param.Empty();
}

namespace SlvsFile {
    static void EmptyExisting();
}

using std::string;
using namespace SolveSpace;
using namespace SolveSpace::Platform;

SlvsFile::SlvsLibClass::TempSV SlvsFile::SlvsLibClass::sv = {};

const SlvsFile::SlvsLibClass::SaveTable SlvsFile::SlvsLibClass::SAVED[] = {
    {'g', "Group.h.v", 'x', &(SlvsFile::SlvsLibClass::sv.g.h.v)},
    {'g', "Group.type", 'd', &(SlvsFile::SlvsLibClass::sv.g.type)},
    {'g', "Group.order", 'd', &(SlvsFile::SlvsLibClass::sv.g.order)},
    {'g', "Group.name", 'S', &(SlvsFile::SlvsLibClass::sv.g.name)},
    {'g', "Group.activeWorkplane.v", 'x', &(SlvsFile::SlvsLibClass::sv.g.activeWorkplane.v)},
    {'g', "Group.opA.v", 'x', &(SlvsFile::SlvsLibClass::sv.g.opA.v)},
    {'g', "Group.opB.v", 'x', &(SlvsFile::SlvsLibClass::sv.g.opB.v)},
    {'g', "Group.valA", 'f', &(SlvsFile::SlvsLibClass::sv.g.valA)},
    {'g', "Group.valB", 'f', &(SlvsFile::SlvsLibClass::sv.g.valB)},
    {'g', "Group.valC", 'f', &(SlvsFile::SlvsLibClass::sv.g.valB)},
    {'g', "Group.color", 'c', &(SlvsFile::SlvsLibClass::sv.g.color)},
    {'g', "Group.subtype", 'd', &(SlvsFile::SlvsLibClass::sv.g.subtype)},
    {'g', "Group.skipFirst", 'b', &(SlvsFile::SlvsLibClass::sv.g.skipFirst)},
    {'g', "Group.meshCombine", 'd', &(SlvsFile::SlvsLibClass::sv.g.meshCombine)},
    {'g', "Group.forceToMesh", 'd', &(SlvsFile::SlvsLibClass::sv.g.forceToMesh)},
    {'g', "Group.predef.q.w", 'f', &(SlvsFile::SlvsLibClass::sv.g.predef.q.w)},
    {'g', "Group.predef.q.vx", 'f', &(SlvsFile::SlvsLibClass::sv.g.predef.q.vx)},
    {'g', "Group.predef.q.vy", 'f', &(SlvsFile::SlvsLibClass::sv.g.predef.q.vy)},
    {'g', "Group.predef.q.vz", 'f', &(SlvsFile::SlvsLibClass::sv.g.predef.q.vz)},
    {'g', "Group.predef.origin.v", 'x', &(SlvsFile::SlvsLibClass::sv.g.predef.origin.v)},
    {'g', "Group.predef.entityB.v", 'x', &(SlvsFile::SlvsLibClass::sv.g.predef.entityB.v)},
    {'g', "Group.predef.entityC.v", 'x', &(SlvsFile::SlvsLibClass::sv.g.predef.entityC.v)},
    {'g', "Group.predef.swapUV", 'b', &(SlvsFile::SlvsLibClass::sv.g.predef.swapUV)},
    {'g', "Group.predef.negateU", 'b', &(SlvsFile::SlvsLibClass::sv.g.predef.negateU)},
    {'g', "Group.predef.negateV", 'b', &(SlvsFile::SlvsLibClass::sv.g.predef.negateV)},
    {'g', "Group.visible", 'b', &(SlvsFile::SlvsLibClass::sv.g.visible)},
    {'g', "Group.suppress", 'b', &(SlvsFile::SlvsLibClass::sv.g.suppress)},
    {'g', "Group.relaxConstraints", 'b', &(SlvsFile::SlvsLibClass::sv.g.relaxConstraints)},
    {'g', "Group.allowRedundant", 'b', &(SlvsFile::SlvsLibClass::sv.g.allowRedundant)},
    {'g', "Group.allDimsReference", 'b', &(SlvsFile::SlvsLibClass::sv.g.allDimsReference)},
    {'g', "Group.scale", 'f', &(SlvsFile::SlvsLibClass::sv.g.scale)},
    {'g', "Group.remap", 'M', &(SlvsFile::SlvsLibClass::sv.g.remap)},
    {'g', "Group.impFile", 'i', NULL},
    {'g', "Group.impFileRel", 'P', &(SlvsFile::SlvsLibClass::sv.g.linkFile)},

    {'p', "Param.h.v.", 'x', &(SlvsFile::SlvsLibClass::sv.p.h.v)},
    {'p', "Param.val", 'f', &(SlvsFile::SlvsLibClass::sv.p.val)},

    {'r', "Request.h.v", 'x', &(SlvsFile::SlvsLibClass::sv.r.h.v)},
    {'r', "Request.type", 'd', &(SlvsFile::SlvsLibClass::sv.r.type)},
    {'r', "Request.extraPoints", 'd', &(SlvsFile::SlvsLibClass::sv.r.extraPoints)},
    {'r', "Request.workplane.v", 'x', &(SlvsFile::SlvsLibClass::sv.r.workplane.v)},
    {'r', "Request.group.v", 'x', &(SlvsFile::SlvsLibClass::sv.r.group.v)},
    {'r', "Request.construction", 'b', &(SlvsFile::SlvsLibClass::sv.r.construction)},
    {'r', "Request.style", 'x', &(SlvsFile::SlvsLibClass::sv.r.style)},
    {'r', "Request.str", 'S', &(SlvsFile::SlvsLibClass::sv.r.str)},
    {'r', "Request.font", 'S', &(SlvsFile::SlvsLibClass::sv.r.font)},
    {'r', "Request.file", 'P', &(SlvsFile::SlvsLibClass::sv.r.file)},
    {'r', "Request.aspectRatio", 'f', &(SlvsFile::SlvsLibClass::sv.r.aspectRatio)},

    {'e', "Entity.h.v", 'x', &(SlvsFile::SlvsLibClass::sv.e.h.v)},
    {'e', "Entity.type", 'd', &(SlvsFile::SlvsLibClass::sv.e.type)},
    {'e', "Entity.construction", 'b', &(SlvsFile::SlvsLibClass::sv.e.construction)},
    {'e', "Entity.style", 'x', &(SlvsFile::SlvsLibClass::sv.e.style)},
    {'e', "Entity.str", 'S', &(SlvsFile::SlvsLibClass::sv.e.str)},
    {'e', "Entity.font", 'S', &(SlvsFile::SlvsLibClass::sv.e.font)},
    {'e', "Entity.file", 'P', &(SlvsFile::SlvsLibClass::sv.e.file)},
    {'e', "Entity.group.v", 'x', &(SlvsFile::SlvsLibClass::sv.e.group.v)},
    {'e', "Entity.point[0].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[0].v)},
    {'e', "Entity.point[1].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[1].v)},
    {'e', "Entity.point[2].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[2].v)},
    {'e', "Entity.point[3].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[3].v)},
    {'e', "Entity.point[4].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[4].v)},
    {'e', "Entity.point[5].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[5].v)},
    {'e', "Entity.point[6].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[6].v)},
    {'e', "Entity.point[7].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[7].v)},
    {'e', "Entity.point[8].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[8].v)},
    {'e', "Entity.point[9].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[9].v)},
    {'e', "Entity.point[10].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[10].v)},
    {'e', "Entity.point[11].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.point[11].v)},
    {'e', "Entity.extraPoints", 'd', &(SlvsFile::SlvsLibClass::sv.e.extraPoints)},
    {'e', "Entity.normal.v", 'x', &(SlvsFile::SlvsLibClass::sv.e.normal.v)},
    {'e', "Entity.distance.v", 'x', &(SlvsFile::SlvsLibClass::sv.e.distance.v)},
    {'e', "Entity.workplane.v", 'x', &(SlvsFile::SlvsLibClass::sv.e.workplane.v)},
    {'e', "Entity.param[0].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.param[0].v)},
    {'e', "Entity.param[1].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.param[1].v)},
    {'e', "Entity.param[2].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.param[2].v)},
    {'e', "Entity.param[3].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.param[3].v)},
    {'e', "Entity.param[4].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.param[4].v)},
    {'e', "Entity.param[5].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.param[5].v)},
    {'e', "Entity.param[6].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.param[6].v)},
    {'e', "Entity.param[7].v", 'x', &(SlvsFile::SlvsLibClass::sv.e.param[7].v)},
    {'e', "Entity.actPoint.x", 'f', &(SlvsFile::SlvsLibClass::sv.e.actPoint.x)},
    {'e', "Entity.actPoint.y", 'f', &(SlvsFile::SlvsLibClass::sv.e.actPoint.y)},
    {'e', "Entity.actPoint.z", 'f', &(SlvsFile::SlvsLibClass::sv.e.actPoint.z)},
    {'e', "Entity.actNormal.w", 'f', &(SlvsFile::SlvsLibClass::sv.e.actNormal.w)},
    {'e', "Entity.actNormal.vx", 'f', &(SlvsFile::SlvsLibClass::sv.e.actNormal.vx)},
    {'e', "Entity.actNormal.vy", 'f', &(SlvsFile::SlvsLibClass::sv.e.actNormal.vy)},
    {'e', "Entity.actNormal.vz", 'f', &(SlvsFile::SlvsLibClass::sv.e.actNormal.vz)},
    {'e', "Entity.actDistance", 'f', &(SlvsFile::SlvsLibClass::sv.e.actDistance)},
    {'e', "Entity.actVisible", 'b', &(SlvsFile::SlvsLibClass::sv.e.actVisible),},


    {'c', "Constraint.h.v", 'x', &(SlvsFile::SlvsLibClass::sv.c.h.v)},
    {'c', "Constraint.type", 'd', &(SlvsFile::SlvsLibClass::sv.c.type)},
    {'c', "Constraint.group.v", 'x', &(SlvsFile::SlvsLibClass::sv.c.group.v)},
    {'c', "Constraint.workplane.v", 'x', &(SlvsFile::SlvsLibClass::sv.c.workplane.v)},
    {'c', "Constraint.valA", 'f', &(SlvsFile::SlvsLibClass::sv.c.valA)},
    {'c', "Constraint.valP.v", 'x', &(SlvsFile::SlvsLibClass::sv.c.valP.v)},
    {'c', "Constraint.ptA.v", 'x', &(SlvsFile::SlvsLibClass::sv.c.ptA.v)},
    {'c', "Constraint.ptB.v", 'x', &(SlvsFile::SlvsLibClass::sv.c.ptB.v)},
    {'c', "Constraint.entityA.v", 'x', &(SlvsFile::SlvsLibClass::sv.c.entityA.v)},
    {'c', "Constraint.entityB.v", 'x', &(SlvsFile::SlvsLibClass::sv.c.entityB.v)},
    {'c', "Constraint.entityC.v", 'x', &(SlvsFile::SlvsLibClass::sv.c.entityC.v)},
    {'c', "Constraint.entityD.v", 'x', &(SlvsFile::SlvsLibClass::sv.c.entityD.v)},
    {'c', "Constraint.other", 'b', &(SlvsFile::SlvsLibClass::sv.c.other)},
    {'c', "Constraint.other2", 'b', &(SlvsFile::SlvsLibClass::sv.c.other2)},
    {'c', "Constraint.reference", 'b', &(SlvsFile::SlvsLibClass::sv.c.reference)},
    {'c', "Constraint.comment", 'S', &(SlvsFile::SlvsLibClass::sv.c.comment)},
    {'c', "Constraint.name", 'S', &(SlvsFile::SlvsLibClass::sv.c.name)},
    {'c', "Constraint.disp.offset.x", 'f', &(SlvsFile::SlvsLibClass::sv.c.disp.offset.x)},
    {'c', "Constraint.disp.offset.y", 'f', &(SlvsFile::SlvsLibClass::sv.c.disp.offset.y)},
    {'c', "Constraint.disp.offset.z", 'f', &(SlvsFile::SlvsLibClass::sv.c.disp.offset.z)},
    {'c', "Constraint.disp.style", 'x', &(SlvsFile::SlvsLibClass::sv.c.disp.style)},

    {'s', "Style.h.v", 'x', &(SlvsFile::SlvsLibClass::sv.s.h.v)},
    {'s', "Style.name", 'S', &(SlvsFile::SlvsLibClass::sv.s.name)},
    {'s', "Style.width", 'f', &(SlvsFile::SlvsLibClass::sv.s.width)},
    {'s', "Style.widthAs", 'd', &(SlvsFile::SlvsLibClass::sv.s.widthAs)},
    {'s', "Style.textHeight", 'f', &(SlvsFile::SlvsLibClass::sv.s.textHeight)},
    {'s', "Style.textHeightAs", 'd', &(SlvsFile::SlvsLibClass::sv.s.textHeightAs)},
    {'s', "Style.textAngle", 'f', &(SlvsFile::SlvsLibClass::sv.s.textAngle)},
    {'s', "Style.textOrigin", 'x', &(SlvsFile::SlvsLibClass::sv.s.textOrigin)},
    {'s', "Style.color", 'c', &(SlvsFile::SlvsLibClass::sv.s.color)},
    {'s', "Style.fillColor", 'c', &(SlvsFile::SlvsLibClass::sv.s.fillColor)},
    {'s', "Style.filled", 'b', &(SlvsFile::SlvsLibClass::sv.s.filled)},
    {'s', "Style.visible", 'b', &(SlvsFile::SlvsLibClass::sv.s.visible)},
    {'s', "Style.exportable", 'b', &(SlvsFile::SlvsLibClass::sv.s.exportable)},
    {'s', "Style.stippleType", 'd', &(SlvsFile::SlvsLibClass::sv.s.stippleType)},
    {'s', "Style.stippleScale", 'f', &(SlvsFile::SlvsLibClass::sv.s.stippleScale)},

    {0, NULL, 0, NULL}
};

static void SlvsFile::EmptyExisting() {
    SK.Empty();
    GetSYS().Empty();
}

//-----------------------------------------------------------------------------
// Clear and free all the dynamic memory associated with our currently-loaded
// sketch. This does not leave the program in an acceptable state (with the
// references created, and so on), so anyone calling this must fix that later.
//-----------------------------------------------------------------------------
void SlvsFile::SlvsLibClass::ClearExisting() {
    SK.Clear();
    GetSYS().Clear();
    FreeAllTemporary();
}

void SlvsFile::SlvsLibClass::LoadUsingTable(const Platform::Path &filename, char *key, char *val) {
    int i;
    for(i = 0; SAVED[i].type != 0; i++) {
        if(strcmp(SAVED[i].desc, key) == 0) {
            SlvsFile::SAVEDptr *p = (SlvsFile::SAVEDptr *)SAVED[i].ptr;
            unsigned int u        = 0;
            switch(SAVED[i].fmt) {
            case 'S': p->S() = val; break;
            case 'b': p->b() = (atoi(val) != 0); break;
            case 'd': p->d() = atoi(val); break;
            case 'f': p->f() = atof(val); break;
            case 'x':
                sscanf(val, "%x", &u);
                p->x() = u;
                break;

            case 'P': {
                Platform::Path path = Platform::Path::FromPortable(val);
                if(!path.IsEmpty()) {
                    p->P() = filename.Parent().Join(path).Expand();
                }
                break;
            }

            case 'c':
                sscanf(val, "%x", &u);
                p->c() = RgbaColor::FromPackedInt(u);
                break;

            case 'M': {
                p->M().clear();
                for(;;) {
                    EntityKey ek;
                    EntityId ei;
                    char line2[1024];
                    if(fgets(line2, (int)sizeof(line2), fh) == NULL)
                        break;
                    if(sscanf(line2, "%d %x %d", &(ei.v), &(ek.input.v), &(ek.copyNumber)) == 3) {
                        if(ei.v == Entity::NO_ENTITY.v) {
                            // Commit bd84bc1a mistakenly introduced code that would remap
                            // some entities to NO_ENTITY. This was fixed in commit bd84bc1a,
                            // but files created meanwhile are corrupt, and can cause crashes.
                            //
                            // To fix this, we skip any such remaps when loading; they will be
                            // recreated on the next regeneration. Any resulting orphans will
                            // be pruned in the usual way, recovering to a well-defined state.
                            continue;
                        }
                        p->M().insert({ek, ei});
                    } else {
                        break;
                    }
                }
                break;
            }

            case 'i': break;

            default: SlvsFile_ConditionThrow(false, "Unexpected value format");
            }
            break;
        }
    }
    if(SAVED[i].type == 0) {
        fileLoadError = true;
    }
}

bool SlvsFile::SlvsLibClass::LoadFromFile(const Platform::Path &filename, bool canCancel) {
    bool fileIsEmpty = true;
    allConsistent    = false;
    fileLoadError    = false;

    fh = OpenFile(filename, "rb");
    if(!fh) {
        SlvsFile_Throw(ssprintf("Couldn't read from file '%s'", filename.raw.c_str()));
        return false;
    }

    EmptyExisting();

    sv = {};
    sv.g.scale = 1; // default is 1, not 0; so legacy files need this
    // Style::FillDefaultStyle(&sv.s);

    char line[1024];
    while(fgets(line, (int)sizeof(line), fh)) {
        fileIsEmpty = false;

        char *s = strchr(line, '\n');
        if(s)   *s = '\0';
        // We should never get files with \r characters in them, but mailers
        // will sometimes mangle attachments.
        s = strchr(line, '\r');
        if(s)   *s = '\0';

        if(*line == '\0')   continue;

        char *e = strchr(line, '=');
        if(e) {
            *e        = '\0';
            char *key = line, *val = e + 1;
            LoadUsingTable(filename, key, val);
        } else if(strcmp(line, "AddGroup") == 0) {
            /*
            // legacy files have a spurious dependency between linked groups
            // and their parent groups, remove
            if(sv.g.type == Group::Type::LINKED)
                sv.g.opA.v = 0;

            SK.group.Add(&(sv.g));
            sv.g       = {};
            sv.g.scale = 1; // default is 1, not 0; so legacy files need this
            */
        } else if(strcmp(line, "AddParam") == 0) {
            // params are regenerated, but we want to preload the values
            // for initial guesses
            SK.param.Add(&(sv.p));
            sv.p = {};
        } else if(strcmp(line, "AddEntity") == 0) {
            // here, entities are not regenerated.
            SK.entity.Add(&(sv.e));
            sv.e = {};
        } else if(strcmp(line, "AddRequest") == 0) {
            /*SK.request.Add(&(sv.r));
            sv.r = {};*/
        } else if(strcmp(line, "AddConstraint") == 0) {
            SK.constraint.Add(&(sv.c));
            sv.c = {};
        } else if(strcmp(line, "AddStyle")==0) {
            /*
            SK.style.Add(&(sv.s));
            sv.s = {};
            Style::FillDefaultStyle(&sv.s);
            */
        } else if(strcmp(line, VERSION_STRING)==0) {
            // do nothing, version string
        } else if(StrStartsWith(line, "Triangle ")      ||
                  StrStartsWith(line, "Surface ")       ||
                  StrStartsWith(line, "SCtrl ")         ||
                  StrStartsWith(line, "TrimBy ")        ||
                  StrStartsWith(line, "Curve ")         ||
                  StrStartsWith(line, "CCtrl ")         ||
                  StrStartsWith(line, "CurvePt ")       ||
                  strcmp(line, "AddSurface")==0         ||
                  strcmp(line, "AddCurve")==0)          {
            // ignore the mesh or shell, since we regenerate that
        } else {
            fileLoadError = true;
        }
    }

    fclose(fh);

    if(fileIsEmpty) {
        SlvsFile_Throw(_("The file is empty. It may be corrupt."));
        return false;
        // NewFile();
    }

    if(fileLoadError) {
        SlvsFile_Throw(_("Unrecognized data in file. This file may be corrupt, or "
                         "from a newer version of the program."));
        // At least leave the program in a non-crashing state.
        if(SK.group.IsEmpty()) {
            return false;
            // NewFile();
        }
    }
    /*if(!ReloadAllLinked(filename, canCancel)) {
            return false;
    }*/
    // UpgradeLegacyData();

    return true;
}

int SlvsFile::SlvsLibClass::StrStartsWith(const char *str, const char *start) {
    return memcmp(str, start, strlen(start)) == 0;
}

void SlvsFile::SlvsLibClass::FirstGenerateSystem() {
    GetSYS().Empty();
    const hGroup &freeG = *SK.groupOrder.Last();
    for(const EntityBase &e : SK.entity) {
        if(e.group.v == freeG.v) {
            for(size_t i = 0; i < 8; i++) {
                const hParam &hp = e.param[i];
                if(hp.v != 0) {
                    Param &p = *SK.param.FindById(hp);
                    GetSYS().param.Add(&p);
                }
            }
        }
    }
    IdList<Param, hParam> params = {};
    for(ConstraintBase &c : SK.constraint) {
        c.Generate(&params);
        if(!params.IsEmpty()) {
            for(Param &p : params) {
                p.h    = SK.param.AddAndAssignId(&p);
                c.valP = p.h;
                GetSYS().param.Add(&p);
            }
            params.Clear();
            c.ModifyToSatisfy();
        }
    }
}

void SlvsFile::SlvsLibClass::ReGenerateSystem() {
    for(Param &p : SK.param) {
        p.known = false;
    }
    for(Param &p : GetSYS().param) {
        p.known = false;
    }
    GetSYS().eq.Empty();
    IdList<Param, hParam> params = {};
    for(ConstraintBase &c : SK.constraint) {
        c.Generate(&params);
        if(!params.IsEmpty()) {
            params.Clear();
            c.ModifyToSatisfy();
        }
    }
}

SolveResult SlvsFile::SlvsLibClass::Solve() {
    ReGenerateSystem();
    Group g            = {};
    hGroup &hg         = *SK.groupOrder.Last();
    g.h.v              = hg.v;
    SolveResult result = GetSYS().Solve(&g, nullptr, nullptr, &g.solved.remove, false, false);
    g.solved.remove.Clear();
    return result;
}

void SlvsFile::SlvsLibClass::Load(const char *filename) {
    LoadFromFile(Platform::Path::From(string(filename)));
    SK.groupOrder.Empty();
    for(const EntityBase &e : SK.entity) {
        const SolveSpace::hGroup& curHG = e.group;

        bool isHaveG = false;
        for(const hGroup &g : SK.groupOrder) {
            if(g.v == curHG.v) {
                isHaveG = true;
                break;
            }
        }

        if(!isHaveG)
            SK.groupOrder.Add(&curHG);
    }
    std::sort(SK.groupOrder.begin(), SK.groupOrder.end(),
              [this](const hGroup &ha, const hGroup &hb) { return ha.v < hb.v; });

    const hGroup &g1st = *SK.groupOrder.First();
    const hGroup &g2nd = *SK.groupOrder.Last();
    const EntityBase *OXYwrkpl = nullptr;
    for(const EntityBase &e : SK.entity) {
        if(EntityBase::Type::WORKPLANE == e.type &&
           e.group.v == g1st.v) {
            OXYwrkpl = &e;
            break;
        }
    }
    SlvsFile_ConditionThrow(nullptr != OXYwrkpl, "Can not find the XOY workplane."); 
    EntityBase &OXYpoint = *SK.GetEntity(OXYwrkpl->point[0]);
    EntityBase &OXYnormal = *SK.GetEntity(OXYwrkpl->normal);
    hEntity hPoint_copy = {0}, hNormal_copy = {0};
    for(EntityBase &e : SK.entity) {
        if(EntityBase::Type::WORKPLANE == e.type && e.group.v == g2nd.v) {
            e.group.v = g1st.v;
            hPoint_copy = e.point[0];
            hNormal_copy = e.normal;
            break;
        }
    }
    SlvsFile_ConditionThrow(0 != hPoint_copy.v, "Can not find the workplane of sketch.");
    EntityBase &point_copy = *SK.GetEntity(hPoint_copy);
    point_copy.group.v     = g1st.v;
    point_copy.type        = EntityBase::Type::POINT_IN_3D;
    for(int i = 0; i < 3; i++)
        point_copy.param[i] = OXYpoint.param[i];
    EntityBase &normal_copy = *SK.GetEntity(hNormal_copy);
    normal_copy.group       = g1st;
    normal_copy.type        = EntityBase::Type::NORMAL_IN_3D;
    for(int i = 0; i < 4; i++)
        normal_copy.param[i] = OXYnormal.param[i];

    FirstGenerateSystem();
}

static SlvsFile::SlvsLibClass SLC = {};
static SlvsFile::SlvsFileException LastException;

static inline Slvs_Exception ToExceptionResult(const SlvsFile::SlvsFileException &ex) {
    Slvs_Exception r = {};
    LastException    = ex;
    r.hadThrow    = true;
    r.message        = const_cast<char *>(LastException.Message().c_str());
    r.file           = const_cast<char *>(LastException.File().c_str());
    r.line           = LastException.Line();
    r.function       = const_cast<char *>(LastException.Function().c_str());
    r.condition      = const_cast<char *>(LastException.Condition().c_str());
    return r;
}

static inline Slvs_Exception ToNoException() {
    Slvs_Exception r = {};
    r.hadThrow        = false;
    r.message     = nullptr;
    r.file        = nullptr;
    r.line        = -1;
    r.function    = nullptr;
    r.condition   = nullptr;
    return r;
}

static inline double ToParam(const Param &p) {
    return p.val;
}

static inline Slvs_Entity ToEntity(const EntityBase &e) {
    Slvs_Entity se = {};
    se.h           = e.h.v;
    se.group       = e.group.v;
    se.type        = (Slvs_EntityType)(uint32_t)e.type;
    se.wrkpl       = e.workplane.v;
    for(int i = 0; i < 4; i++)
        se.point[i] = e.point[i].v;
    se.normal = e.normal.v;
    se.distance = e.distance.v;
    for(int i = 0; i < 4; i++)
        se.param[i] = e.param[i].v;
    se.construction = e.construction ? 1 : 0;
    return se;
}

static inline Slvs_Constraint ToConstraint(const ConstraintBase &c) {
    Slvs_Constraint sc = {};
    sc.h           = c.h.v;
    sc.group       = c.group.v;
    sc.type        = (Slvs_ConstraintType)(uint32_t)c.type;
    sc.wrkpl       = c.workplane.v;
    sc.valA            = c.valA;
    sc.ptA             = c.ptA.v;
    sc.ptB             = c.ptB.v;
    sc.entityA         = c.entityA.v;
    sc.entityB         = c.entityB.v;
    sc.entityC         = c.entityC.v;
    sc.entityD         = c.entityD.v;
    sc.other           = c.other ? 1 : 0;
    sc.other2          = c.other2 ? 1 : 0;
    sc.name            = const_cast<char *>(c.name.c_str());
    return sc;
}

extern "C" {

Slvs_Exception Slvs_Load(char *filename) {
    try {
        SLC.Load(filename);
        return ToNoException();
    } catch(SlvsFile::SlvsFileException &ex) {
        return ToExceptionResult(ex);
    }
}

Slvs_Exception Slvs_File_Solve(Slvs_SolveResult *r) {
    try {
        SolveResult sr = SLC.Solve();
        *r             = (Slvs_SolveResult)(uint32_t)sr;
        return ToNoException();
    } catch(SlvsFile::SlvsFileException &ex) {
        return ToExceptionResult(ex);
    }
}

Slvs_Exception Slvs_GetParam(double *val, Slvs_hParam v) {
    try {
        hParam h = {v};
        Param *p = SK.param.FindByIdNoOops(h);
        SlvsFile_ConditionThrow(p != nullptr, "Can not find the param.");
        *val = ToParam(*p);
        return ToNoException();
    } catch(SlvsFile::SlvsFileException &ex) {
        return ToExceptionResult(ex);
    }
}

Slvs_Exception Slvs_GetEntity(Slvs_Entity *e, Slvs_hEntity v) {
    try {
        hEntity h = {v};
        EntityBase *eb = SK.entity.FindByIdNoOops(h);
        SlvsFile_ConditionThrow(eb != nullptr, "Can not find the entity.");
        *e = ToEntity(*eb);
        return ToNoException();
    } catch(SlvsFile::SlvsFileException &ex) {
        return ToExceptionResult(ex);
    }
}

Slvs_Exception Slvs_GetConstraint(Slvs_Constraint *s, Slvs_hConstraint v) {
    try {
        hConstraint h      = {v};
        ConstraintBase *cb = SK.constraint.FindByIdNoOops(h);
        SlvsFile_ConditionThrow(cb != nullptr, "Can not find the constraint.");
        *s       = ToConstraint(*cb);
        return ToNoException();
    } catch(SlvsFile::SlvsFileException &ex) {
        return ToExceptionResult(ex);
    }
}

Slvs_Exception Slvs_SetConstraintVal(Slvs_Constraint *s, Slvs_hConstraint v, double val) {
    try {
        hConstraint h = {v};
        ConstraintBase *cb = SK.constraint.FindByIdNoOops(h);
        SlvsFile_ConditionThrow(cb != nullptr, "Can not find the constraint.");
        cb->valA = val;
        *s = ToConstraint(*cb);
        return ToNoException();
    } catch(SlvsFile::SlvsFileException &ex) {
        return ToExceptionResult(ex);
    }
}

}

//void SlvsFile::SlvsLibClass::ChangeConstraintVal(uint32_t v, double val){
//    hConstraint hc = {};
//    hc.v           = v;
//    ConstraintBase &c = *SK.GetConstraint(hc);
//    c.valA            = val;
//}
//
//const char *SlvsFile::SlvsLibClass::GetConstraintName(uint32_t v) {
//    hConstraint hc    = {};
//    hc.v              = v;
//    ConstraintBase &c = *SK.GetConstraint(hc);
//    return c.name.c_str();
//}
