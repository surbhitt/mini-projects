#include <iostream>
using namespace std;

int main() {
    string s = "#include <iostream>\nusing namespace std;\n\nint main() {\n    string s = \"?\"; \n    int n = s.length();\n    for (int i = 0; i < n; i++) {\n        if (s[i] == 63)\n            for (int j = 0; j < n; j++) {\n                switch (s[j]) {\n                case '\\n':\n                    cout << \"\\\\n\";\n                    break;\n                case '\\\"':\n                    cout << \"\\\\\\\"\";\n                    break;\n                case '\\\\':\n                    cout << \"\\\\\\\\\";\n                    break;\n                default:\n                    cout << s[j];\n                }\n            }\n        else\n            cout << s[i];\n    }\n}\n"; 
    int n = s.length();
    for (int i = 0; i < n; i++) {
        if (s[i] == 63)
            for (int j = 0; j < n; j++) {
                switch (s[j]) {
                case '\n':
                    cout << "\\n";
                    break;
                case '\"':
                    cout << "\\\"";
                    break;
                case '\\':
                    cout << "\\\\";
                    break;
                default:
                    cout << s[j];
                }
            }
        else
            cout << s[i];
    }
}
