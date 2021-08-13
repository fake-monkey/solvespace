#define LIBRARY
#include <iostream>
#include "solvespace.h"
#include "SlvsFile/SlvsFile.h"
#include "platform/platform.h"
#include "slvs.h"
#pragma comment(lib, "../bin/Debug/slvs.lib")

extern "C" {
int demo_main();
}

static SlvsFile::SlvsLibClass ssui = {};
using std::cout;
using std::string;

typedef struct {
    string name;
    uint32_t hCv;
    double val;
} TestTable;

void test_file_main() {
    TestTable tt[] = {
        {"triangle", 0x00000008, 100},
        {"sixedge", 0x00000014, 100},
        {"equilateral_triangle", 0x0000000a, 100},
        {"fillet", 0x00000012, 100},
        {"fillet", 0x00000014, 20},
        {"center_rectangle", 0x00000010, 100},
        {"XYDis", 0x00000008, 80},
        {"angle_test", 0x00000007, 45},
    };
    const TestTable& cur = tt[7];
    string allname       = R"(D:\Liu_Xin_files\SOLVESPACE\save_file\)" + cur.name + ".slvs";
    cout << allname << "\n\n";
    ssui.Load(allname.c_str());
    SolveSpace::SolveResult a = ssui.Solve();
    cout << "result 1: " << (uint32_t)a << "\n\n";
    uint32_t v = cur.hCv;
    ssui.ChangeConstraintVal(v, cur.val);
    a = ssui.Solve();
    cout << "result 2: " << (uint32_t)a << "\n\n";
    for(Param& p : ssui.GetSK().param) {
        cout << std::hex << p.h.v << "\n";
        cout << p.val << "\n";
        cout << "\n";
    }
}

int main() {
    demo_main();
    //test_file_main();
    return 0;
}
