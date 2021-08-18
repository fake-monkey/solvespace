#pragma once
#include "solvespace.h"
#include "SlvsFile/GetSYS.h"
#include <slvs.h>

#ifdef _DEBUG
#   define DebugDLL DLL
#else
#   define DebugDLL
#endif

namespace SlvsFile {
    using std::string;

class DebugDLL SlvsFileException {
public:
    SlvsFileException() : _message(""), _file(""), _line(-1), _function(""), _condition("") {
    }
    SlvsFileException(const char *message)
        : _message(message), _file(""), _line(-1), _function(""), _condition("") {
    }
    SlvsFileException(const char *file, int line, const char *function, const string &message)
        : _message(message), _file(file), _line(line), _function(function), _condition("") {
    }
    SlvsFileException(const char *file, int line, const char *function, const char *condition,
                      const string &message)
        : _message(message), _file(file), _line(line), _function(function), _condition(condition) {
    }
    const string &Message() const {
        return _message;
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
    string _message;
    string _file;
    int _line;
    string _function;
    string _condition;
};

class DebugDLL SlvsLibClass {
private:
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

    void EmptyExisting();
    void LoadUsingTable(const Platform::Path &filename, char *key, char *val);
    bool LoadFromFile(const Platform::Path &filename, bool canCancel = false);
    int StrStartsWith(const char *str, const char *start);
    void FirstGenerateSystem();
    void ReGenerateSystem();

public:
    void ClearExisting();
    ~SlvsLibClass() {
        //ClearExisting();
    }
    Sketch &GetSK() {
        return SK;
    }
    SolveResult Solve();
    void Load(const char *filename);
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

#define SlvsFile_Throw(message) \
    throw SlvsFile::SlvsFileException(__FILE__, __LINE__, __FUNCTION__, message);

#define SlvsFile_ConditionThrow(condition, message) \
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
        int hadThrow;
        char *message;
        char *file;
        int line;
        char *function;
        char *condition;
    } Slvs_Exception;

    DLL Slvs_Exception Slvs_Load(Slvs_System *sys, char *filename);
    DLL Slvs_Exception Slvs_File_Solve(Slvs_SolveResult *r);

    DLL Slvs_Exception Slvs_GetParamByID(Slvs_Param *p, Slvs_hParam v);
    DLL Slvs_Exception Slvs_GetEntityByID(Slvs_Entity *e, Slvs_hEntity v);
    DLL Slvs_Exception Slvs_GetConstraintByID(Slvs_Constraint *s, Slvs_hConstraint v);
    DLL Slvs_Exception Slvs_SetConstraintValByID(Slvs_Constraint *c, Slvs_hConstraint v,
                                                 double val);

    DLL Slvs_Exception Slvs_GetParamByIndex(Slvs_Param *p, int i);
    DLL Slvs_Exception Slvs_GetEntityByIndex(Slvs_Entity *e, int i);
    DLL Slvs_Exception Slvs_GetConstraintByIndex(Slvs_Constraint *c, int i);

    DLL void Slvs_ClearExisting();

#ifdef __cplusplus
}
#endif
