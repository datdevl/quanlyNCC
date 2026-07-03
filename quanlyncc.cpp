#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <windows.h>
using namespace std;

// ================== C?U TRÚC D? LI?U ==================
struct NhaCungCap {
    string maNCC, ten, diaChi, sdt, email;
    double tienVon;
};

struct Node {
    NhaCungCap data;
    Node *left, *right;
};
typedef Node* Tree;

// ================== HÀM HO TRO ==================
string formatMoney(double money) {
    long long m = (long long)money;
    string s = to_string(m);
    int n = s.length();
    for (int i = n - 3; i > 0; i -= 3) {
        s.insert(i, ".");
    }
    return s;
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

string toUpper(string s) {
    for (int i = 0; i < (int)s.length(); i++)
        s[i] = toupper(s[i]);
    return s;
}

string chuanHoa(string s) {
    if (s.empty()) return s;
    while (!s.empty() && isspace(s[0])) s.erase(0, 1);
    while (!s.empty() && isspace(s[s.length() - 1])) s.erase(s.length() - 1);

    string res = "";
    for (int i = 0; i < (int)s.length(); i++) {
        if (isspace(s[i])) {
            if (!res.empty() && res[res.length() - 1] != ' ') res += ' ';
        } else {
            res += toupper(s[i]);
        }
    }
    return res;
}

bool checkSDT(string sdt) {
    if (sdt.length() != 10) return false;
    if (sdt[0] != '0') return false;
    for (int i = 0; i < sdt.length(); i++) {
        if (sdt[i] < '0' || sdt[i] > '9') return false;
    }
    return true;
}

// ================== HIEU UNG LOADING  ==================
void loading(string text = "Dang xu ly", int time_ms = 800) {
    setColor(11);
    cout << "\n\t" << text << " ";
    char load[] = {'|', '/', '-', '\\'};
    int colors[] = {9, 11, 14, 10, 13};
    
    for (int i = 0; i < 20; i++) {
        setColor(colors[i % 5]);
        cout << load[i % 4] << flush;
        Sleep(time_ms / 20);
        cout << "\b";
    }
    setColor(10);
    cout << " HOAN TAT!" << endl << endl;
    setColor(7);
}

void loadingBar(string text = "Dang tai") {
    setColor(14);
    cout << "\n\t" << text << "\n\t[";
    setColor(11);
    for (int i = 0; i <= 50; i++) {
        cout << "=" << flush;
        Sleep(25);
        if (i % 10 == 0) {
            setColor(10);
            cout << " " << i*2 << "% ";
            setColor(11);
        }
    }
    setColor(10);
    cout << "] HOAN TAT 100%" << endl << endl;
    setColor(7);
}

// ================== BST ==================
void init(Tree &t) { t = NULL; }

void insertNode(Tree &t, NhaCungCap x) {
    if (t == NULL) {
        t = new Node;
        t->data = x;
        t->left = t->right = NULL;
    } else if (x.maNCC < t->data.maNCC)
        insertNode(t->left, x);
    else if (x.maNCC > t->data.maNCC)
        insertNode(t->right, x);
}

Node* searchMa(Tree t, string ma) {
    if (!t || t->data.maNCC == ma) return t;
    if (ma < t->data.maNCC)
        return searchMa(t->left, ma);
    return searchMa(t->right, ma);
}

// ================== HI?N TH? ==================
void header() {
    setColor(14);
    cout << "\n" << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    cout << left << setw(10) << "MA NCC" << setw(30) << "TEN NHA CUNG CAP"
         << setw(40) << "DIA CHI" << setw(15) << "SDT" << right << setw(20) << "TIEN VON (VND)" << left << endl;
    cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    setColor(7);
}

void xuat1(NhaCungCap x) {
    cout << left << setw(10) << x.maNCC << setw(30) << x.ten
         << setw(40) << x.diaChi << setw(15) << x.sdt
         << right << setw(20) << formatMoney(x.tienVon) << left << endl;
}

void duyetLNR(Tree t) {
    if (t) {
        duyetLNR(t->left);
        xuat1(t->data);
        duyetLNR(t->right);
    }
}

int demNode(Tree t) { return t ? 1 + demNode(t->left) + demNode(t->right) : 0; }
double tongVon(Tree t) { return t ? t->data.tienVon + tongVon(t->left) + tongVon(t->right) : 0; }
int chieuCao(Tree t) { return t ? 1 + max(chieuCao(t->left), chieuCao(t->right)) : 0; }

int demLa(Tree t) {
    if (!t) return 0;
    if (!t->left && !t->right) return 1;
    return demLa(t->left) + demLa(t->right);
}

void findMaxV(Tree t, Node* &res) {
    if (!t) return;
    if (!res || t->data.tienVon > res->data.tienVon) res = t;
    findMaxV(t->left, res);
    findMaxV(t->right, res);
}

void findMinV(Tree t, Node* &res) {
    if (!t) return;
    if (!res || t->data.tienVon < res->data.tienVon) res = t;
    findMinV(t->left, res);
    findMinV(t->right, res);
}

void locVonLon(Tree t) {
    if (!t) return;
    locVonLon(t->left);
    if (t->data.tienVon > 500000000) xuat1(t->data);
    locVonLon(t->right);
}

void timTheoTen(Tree t, string key, vector<NhaCungCap> &ds) {
    if (!t) return;
    timTheoTen(t->left, key, ds);
    if (toUpper(t->data.ten).find(toUpper(key)) != string::npos)
        ds.push_back(t->data);
    timTheoTen(t->right, key, ds);
}

void timTheoSDT(Tree t, string key, vector<NhaCungCap> &ds) {
    if (!t) return;
    timTheoSDT(t->left, key, ds);
    if (t->data.sdt.find(key) != string::npos) ds.push_back(t->data);
    timTheoSDT(t->right, key, ds);
}

void timTheoDiaChi(Tree t, string key, vector<NhaCungCap> &ds) {
    if (!t) return;
    timTheoDiaChi(t->left, key, ds);
    if (toUpper(t->data.diaChi).find(toUpper(key)) != string::npos)
        ds.push_back(t->data);
    timTheoDiaChi(t->right, key, ds);
}

// ================== XÓA ==================
Node* findMaxLeft(Tree t) {
    while (t && t->right) t = t->right;
    return t;
}

void deleteNode(Tree &t, string ma) {
    if (!t) return;
    if (ma < t->data.maNCC) deleteNode(t->left, ma);
    else if (ma > t->data.maNCC) deleteNode(t->right, ma);
    else {
        Node* p = t;
        if (!t->left) t = t->right;
        else if (!t->right) t = t->left;
        else {
            Node* s = findMaxLeft(t->left);
            t->data = s->data;
            deleteNode(t->left, s->data.maNCC);
            return;
        }
        delete p;
    }
}

void xoaToanBo(Tree &t) {
    if (t) {
        xoaToanBo(t->left);
        xoaToanBo(t->right);
        delete t;
        t = NULL;
    }
}

// ================== FILE IO ==================
void loadFile(Tree &t) {
    ifstream f("database.txt");
    if (!f) {
        setColor(12); cout << "Loi: Khong tim thay file database.txt!\n"; setColor(7);
        return;
    }
    string line;
    int c = 0;
    while (getline(f, line)) {
        if (line.empty()) continue;
        if (!line.empty() && line[line.length() - 1] == '\r')
            line.erase(line.length() - 1);

        stringstream ss(line);
        NhaCungCap x;
        string v;

        getline(ss, x.maNCC, '|');
        getline(ss, x.ten, '|');
        getline(ss, x.diaChi, '|');
        getline(ss, x.sdt, '|');
        getline(ss, v);
        x.tienVon = atof(v.c_str());

        // Xử lý trùng mã NCC
        string maGoc = x.maNCC;
        int count = 2;
        while (searchMa(t, x.maNCC)) {
            x.maNCC = maGoc + "#" + to_string(count);
            count++;
        }

        insertNode(t, x);
        c++;
    }
    f.close();
    setColor(10); cout << "===> DA NAP THANH CONG " << c << " NHA CUNG CAP!\n"; setColor(7);
}

void saveFile(Tree t, ofstream &f) {
    if (t) {
        saveFile(t->left, f);
        f << t->data.maNCC << "|" << t->data.ten << "|" << t->data.diaChi 
          << "|" << t->data.sdt << "|" << (long long)t->data.tienVon << endl;
        saveFile(t->right, f);
    }
}

// ================== MENU Ð?P ==================
void showMenu() {
    system("cls");
    setColor(11);
    cout << " +---------------------------------------------------------------+\n";
    cout << " |              HE THONG QUAN LY NHA CUNG CAP (BST)              |\n";
    cout << " +---------------------------------------------------------------+\n";
    setColor(14);
    cout << " |  1. Them NCC moi              | 11. Loc von > 500 trieu       |\n";
    cout << " |  2. Xuat danh sach            | 12. Dem so nut la             |\n";
    cout << " |  3. Tim kiem theo MA          | 13. Tinh chieu cao cay        |\n";
    cout << " |  4. Tim kiem theo TEN         | 14. Tim kiem theo SDT         |\n";
    cout << " |  5. Sua thong tin theo MA     | 15. Luu du lieu vao File      |\n";
    cout << " |  6. Xoa NCC theo MA           | 16. Doc du lieu tu File       |\n";
    cout << " |  7. Tinh tong von             | 17. Xoa sach toan bo cay      |\n";
    cout << " |  8. Dem tong so NCC           | 18. Thong tin tac gia         |\n";
    cout << " |  9. Tim NCC von LON NHAT      | 19. Tim kiem theo DIA CHI     |\n";
    cout << " | 10. Tim NCC von NHO NHAT      | 20. Xuat full & Thong ke      |\n";
    setColor(12);
    cout << " |  0. THOAT CHUONG TRINH                                        |\n";
    setColor(11);
    cout << " +---------------------------------------------------------------+\n";
    setColor(7);
    cout << " Nhap lua chon cua ban: ";
}

// ================== MAIN ==================
int main() {
    Tree t;
    init(t);
    int chon;
    string s;

    // Loading khi kh?i d?ng
    system("cls");
    setColor(13);
    cout << "\n\n\t============================================================\n";
    cout << "\t|          HE THONG QUAN LY NHA CUNG CAP (BST)             |\n";
    cout << "\t============================================================\n\n";
    loadingBar("Dang khoi dong he thong");
    Sleep(500);

    do {
        showMenu();

        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(1000, '\n');
            setColor(12);
            cout << "\nLua chon khong hop le! Vui long nhap mot so.\n";
            setColor(7);
            cout << "\nNhan Enter de ve menu...";
            cin.ignore(1000, '\n');
            cin.get();
            continue;
        }

        cin.ignore(1000, '\n');

        if (chon < 0 || chon > 20) {
            setColor(12);
            cout << "\nLua chon khong hop le! Chi duoc nhap tu 0 den 20.\n";
            setColor(7);
            cout << "\nNhan Enter de ve menu...";
            cin.get();
            continue;
        }

        switch (chon) {
            case 1: {
                NhaCungCap x;
                cout << "Ma NCC: "; cin >> x.maNCC;
                x.maNCC = toUpper(x.maNCC);
                if (searchMa(t, x.maNCC)) {
                    setColor(12); cout << "Loi: Ma da ton tai!\n"; setColor(7);
                } else {
                    cin.ignore();
                    cout << "Ten NCC: "; getline(cin, x.ten); x.ten = chuanHoa(x.ten);
                    cout << "Dia chi : "; getline(cin, x.diaChi); x.diaChi = chuanHoa(x.diaChi);
                    do {
                        cout << "SDT     : "; cin >> x.sdt;
                        if (!checkSDT(x.sdt)) {
                            setColor(12); cout << "Loi: SDT phai gom 10 chu so va bat dau bang so 0!\n"; setColor(7);
                        }
                    } while (!checkSDT(x.sdt));

                    do {
                        cout << "Von     : "; cin >> x.tienVon;
                        if (x.tienVon < 0) {
                            setColor(12); cout << "Loi: Tien von khong duoc am!\n"; setColor(7);
                        }
                    } while (x.tienVon < 0);
                    insertNode(t, x);
                    setColor(10); cout << "Da them thanh cong!\n"; setColor(7);
                }
                break;
            }

            case 2:
                if (t) { header(); duyetLNR(t); }
                else cout << "Cay hien dang trong!\n";
                break;

            case 3: {
                cout << "Nhap ma NCC: "; cin >> s;
                Node* p = searchMa(t, toUpper(s));
                if (p) { header(); xuat1(p->data); }
                else cout << "Khong tim thay!\n";
                break;
            }

            case 4: {
                cout << "Nhap ten can tim: "; getline(cin, s);
                vector<NhaCungCap> ds;
                timTheoTen(t, s, ds);
                if (ds.empty()) cout << "Khong tim thay!\n";
                else { header(); for (size_t i = 0; i < ds.size(); i++) xuat1(ds[i]); }
                break;
            }

            case 5: {
                cout << "Nhap ma NCC can sua: "; cin >> s;
                Node* p = searchMa(t, toUpper(s));
                if (!p) { cout << "Khong tim thay!\n"; break; }

                header(); xuat1(p->data);
                cout << "\n--- Nhap thong tin moi (De trong neu khong muon doi) ---\n";
                cin.ignore();

                string temp;
                cout << "Ten moi (" << p->data.ten << "): "; getline(cin, temp);
                if (!temp.empty()) p->data.ten = chuanHoa(temp);

                cout << "Dia chi moi (" << p->data.diaChi << "): "; getline(cin, temp);
                if (!temp.empty()) p->data.diaChi = chuanHoa(temp);

                do {
                    cout << "SDT moi (" << p->data.sdt << "): "; getline(cin, temp);
                    if (!temp.empty()) {
                        if (!checkSDT(temp)) {
                            setColor(12); cout << "Loi: SDT phai gom 10 chu so va bat dau bang so 0!\n"; setColor(7);
                        } else {
                            p->data.sdt = temp;
                            break;
                        }
                    } else {
                        break; // Nguoi dung an Enter de bo qua
                    }
                } while (true);

                do {
                    cout << "Von moi (" << formatMoney(p->data.tienVon) << "): "; getline(cin, temp);
                    if (!temp.empty()) {
                        double newVon = atof(temp.c_str());
                        if (newVon < 0) {
                            setColor(12); cout << "Loi: Tien von khong duoc am!\n"; setColor(7);
                        } else {
                            p->data.tienVon = newVon;
                            break;
                        }
                    } else {
                        break; // Nguoi dung an Enter de bo qua
                    }
                } while (true);

                setColor(10); cout << "Da cap nhat thanh cong!\n"; setColor(7);
                break;
            }

            case 6:
                cout << "Nhap ma NCC can xoa: "; cin >> s;
                deleteNode(t, toUpper(s));
                cout << "Da xoa thanh cong!\n";
                break;

            case 7:
                cout << "Tong von dau tu: " << formatMoney(tongVon(t)) << " VND\n";
                break;

            case 8:
                cout << "Tong so NCC: " << demNode(t) << endl;
                break;

            case 9: {
                Node* mx = NULL;
                findMaxV(t, mx);
                if (mx) { header(); xuat1(mx->data); }
                else cout << "Cay trong!\n";
                break;
            }

            case 10: {
                Node* mn = NULL;
                findMinV(t, mn);
                if (mn) { header(); xuat1(mn->data); }
                else cout << "Cay trong!\n";
                break;
            }

            case 11:
                setColor(14); cout << "\n=== DANH SACH VON > 500 TRIEU ===\n\n"; setColor(7);
                header();
                locVonLon(t);
                break;

            case 12:
                cout << "So nut la: " << demLa(t) << endl;
                break;

            case 13:
                cout << "Chieu cao cay: " << chieuCao(t) << endl;
                break;

            case 14: {
                cout << "Nhap SDT: "; cin >> s;
                vector<NhaCungCap> ds;
                timTheoSDT(t, s, ds);
                if (ds.empty()) cout << "Khong tim thay!\n";
                else { header(); for (size_t i = 0; i < ds.size(); i++) xuat1(ds[i]); }
                break;
            }

            case 15:
                loading("Dang luu du lieu vao file");
                {
                    ofstream f("database.txt");
                    if (f) {
                        saveFile(t, f);
                        f.close();
                        setColor(10); cout << "Da luu du lieu thanh cong!\n"; setColor(7);
                    }
                }
                break;

            case 16:
                loadingBar("Dang doc du lieu tu file");
                loadFile(t);
                break;

            case 17:
                loading("Dang xoa toan bo du lieu");
                xoaToanBo(t);
                cout << "Da xoa toan bo cay!\n";
                break;

            case 18:
                setColor(13);
                cout << "\n--- THONG TIN TAC GIA ---\n";
                cout << "Ho ten: [Nhap ten cua ban]\nMSSV: 1971020090\nLop: CTDL-GT\n";
                setColor(7);
                break;

            case 19: {
                cout << "Nhap dia chi: "; getline(cin, s);
                vector<NhaCungCap> ds;
                timTheoDiaChi(t, s, ds);
                if (ds.empty()) cout << "Khong tim thay!\n";
                else { header(); for (size_t i = 0; i < ds.size(); i++) xuat1(ds[i]); }
                break;
            }

            case 20:
                if (!t) cout << "Hay chon 16 de nap du lieu truoc!\n";
                else {
                    header();
                    duyetLNR(t);
                    setColor(10);
                    cout << "\n>>> THONG KE <<<\n";
                    cout << "Tong so NCC     : " << demNode(t) << endl;
                    cout << "Tong von        : " << formatMoney(tongVon(t)) << " VND\n";
                    cout << "Chieu cao       : " << chieuCao(t) << endl;
                    cout << "So nut la       : " << demLa(t) << endl;
                    Node* mx = NULL; findMaxV(t, mx);
                    if (mx) cout << "NCC von cao nhat: " << mx->data.ten << endl;
                    setColor(7);
                }
                break;

            case 0:
                loading("Dang thoat chuong trinh", 600);
                cout << "\nTam biet va hen gap lai!\n";
                break;
        }

        if (chon != 0) {
            cout << "\nNhan Enter de ve menu...";
            cin.ignore(1000, '\n');
            cin.get();
        }
    } while (chon != 0);

    xoaToanBo(t);
    return 0;
}
