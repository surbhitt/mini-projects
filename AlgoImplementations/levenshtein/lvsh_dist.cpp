/* #include <cassert> */
#include <algorithm>
#include <string>
using namespace std;

int lvsh_dist(string a, string b) {
    if(a.size() == 0) return b.size();
    if(b.size() == 0) return a.size();
    int lv_t_ab = lvsh_dist(a.substr(1), b.substr(1));
    if (a[0] == b[0]) return lv_t_ab;
    int lv_t_a = lvsh_dist(a.substr(1), b);
    int lv_t_b = lvsh_dist(a, b.substr(1));
    return 1 + min({lv_t_a, lv_t_b, lv_t_ab});
}

/* int main(int argc, char** argv) { */
/*     assert(argc == 3); */
/*     cout << lvsh_dist(argv[1], argv[2]) << endl; */
/*     return 0; */
/* } */
