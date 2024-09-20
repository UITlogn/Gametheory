#include <bits/stdc++.h>
using namespace std;

bool checkFileWithFstream(string path) {
    ifstream isf(path);
    return isf.good();
}
signed main() {
    bool onlinejudge = 0;
    string NAME = "GGAME";

    if (checkFileWithFstream(NAME + ".cpp")) return 0;
    ofstream fcpp(NAME + ".cpp");
    ofstream finp(NAME + ".inp");
    ofstream fout(NAME + ".out");

    fcpp << "#include <bits/stdc++.h>                                                                                                                   //Vu Hoang Long\n";
    fcpp << "using namespace std;\n";
    fcpp << "#define int long long\n\n";
    fcpp << "signed main() {\n";
    fcpp << "    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);\n";
    if (onlinejudge) fcpp << "    #ifndef ONLINE_JUDGE\n";
    fcpp << "    freopen(\"" << NAME << ".inp\", \"r\", stdin);\n";
    fcpp << "    freopen(\"" << NAME << ".out\", \"w\", stdout);\n";
    if (onlinejudge) fcpp << "    #endif\n";
    fcpp << "\n    return 0;\n";
    fcpp << "}";
    fcpp.close();
    return 0;
}