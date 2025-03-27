#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#define Capacity 200
using namespace std;

class LOLDic
{
    string name, position;
    double hp{}, mp{}, speed{}, range{};

public:
    void InsertDic(const string& n, double h, double m, double s, double r, const string& pos)
    {
        name = n;
        position = pos;
        hp = h;
        mp = m;
        speed = s;
        range = r;
    }

    void Show() const
    {
        cout << "이름: " << name << " | "
            << "HP: " << hp << " | "
            << "MP: " << mp << " | "
            << "속도: " << speed << " | "
            << "사거리: " << range << " | "
            << "포지션: " << position << endl;
    }

    string ShowName()
    {
        return name;
    }

    string ShowPos()
    {
        return position;
    }
    
    double ShowHp() const
    {
        return hp;
    }
};

void InSertTestData();
void ShowMenu();
int ExcuteCommand(int CommandNum);
void quick_sort(int start, int end);

void Search();
int InSert();
void Delete();
void DeleteAll();
void PrintAll();
void FindMaxHp();
void SortByHp();

LOLDic* Dictionary[Capacity];
int CountDic{};

int main()
{
    InSertTestData();

    while (true)
    {

        int CommandNum{};

        ShowMenu();
        if (!(cin >> CommandNum))
        {
            system("cls");
            cout << "\n잘못된 입력입니다. 숫자를 입력하세요." << endl;
            cin.clear();  // 입력 스트림 플래그 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 입력 버퍼 비우기
            continue;
        }

        if (CommandNum == 0)
            break;

        if (ExcuteCommand(CommandNum) == 1) {
            system("cls");
            cout << "잘못된 입력입니다. 다시 입력해주세요. " << endl;
            continue;
        }
    }

    for (int i = 0; i < 200; ++i) {
        delete Dictionary[i];
    }
}

void ShowMenu()
{
    cout << "--------" << "**Menu**" << "--------" << endl;
    cout << "\t" << "1. Search" << endl;
    cout << "\t" << "2. Insert" << endl;
    cout << "\t" << "3. Delete" << endl;
    cout << "\t" << "4. DeleteAll" << endl;
    cout << "\t" << "5. PrintAll" << endl;
    cout << "\t" << "6. FindMaxHp" << endl;
    cout << "\t" << "7. SortByHp" << endl;
    cout << "0을 누르면 종료됩니다." << endl;
    cout << "커멘드 번호를 입력해주세요. : ";
}

int ExcuteCommand(int CommandNum)
{
    if (CommandNum == 1) {
        Search();
        return 0;
    }
    else if (CommandNum == 2) {
        while (true) {
            int State{};
            State = InSert();
            if (State == -1) {
                system("cls");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "입력에 오류가 있습니다. 다시 입력해주세요." << endl;
                continue;
            }
            else if (State == -2) {
                system("cls");
                cout << "중복되는 이름이 있습니다. 다시 입력해주세요." << endl;
                continue;
            }
            else if (State == -3) {
                system("cls");
                cout << "디렉토리가 꽉 찼습니다. \n";
                break;
            }
            else break;
        }
        return 0;
    }
    else if (CommandNum == 3) {
        Delete();
        return 0;
    }
    else if (CommandNum == 4) {
        DeleteAll();
        return 0;
    }
    else if (CommandNum == 5) {
        PrintAll();
        return 0;
    }
    else if (CommandNum == 6) {
        FindMaxHp();
        return 0;
    }
    else if (CommandNum == 7) {
        SortByHp();
        return 0;
    }
    else {
        return 1;
    }
}

void Search()
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }

    system("cls");
    string Sname;
    cout << "검색할 챔피언의 이름을 입력해주세요. : ";
    cin >> Sname;

    system("cls");
    for (int i = 0; i < CountDic; i++) {
        if (Sname == Dictionary[i]->ShowName()) {
            Dictionary[i]->Show();
        }
    }
}

int InSert()
{
    if (CountDic == 200) {
        cout << "디렉토리가 꽉 찼습니다.\n";
        return -3;
    }

    Dictionary[CountDic] = new LOLDic();
    int hp, mp, speed, range;
    string name, position;

    cout << "추가할 챔피언 정보를 입입력해주세요. " << endl;
    cout << "주의 : 입력 순서는 이름, 체력, 마나, 속도, 사거리, 포지션 입니다. " << endl;
    cout << "입력이 부족하다면 계속 입력을 기다리기에 꼭 6개의 입력을 해주세요." << endl;

    if (!(cin >> name >> hp >> mp >> speed >> range >> position)) {
        return -1;
    }
    for (int i = 0; i < CountDic; i++) {
        if (Dictionary[i]->ShowName() == name) {
            return -2;
        }
    }

    Dictionary[CountDic++]->InsertDic(name, hp, mp, speed, range, position);
    system("cls");

    return 0;
}

void Delete()
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }

    system("cls");
    string Dname;
    cout << "삭제할 챔피언의 이름을 입력해주세요. : ";
    cin >> Dname;

    for (int i = 0; i < CountDic; i++) {
        if (Dname == Dictionary[i]->ShowName()) {
            delete Dictionary[i];
            for (int j = i; j < CountDic - 1; j++) {
                Dictionary[j] = Dictionary[j + 1];
            }
            CountDic--;
            cout << "성공적으로 삭제하였습니다.\n";
            break;
        }
        cout << "해당 챔피언의 정보가 없어 삭제된 항목이 없습니다.\n";
    }

    system("cls");
}

void DeleteAll()
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }

    system("cls");
    string Pos;
    bool flag{ false };
    cout << "삭제할 포지션을 입력해주세요. : ";
    cin >> Pos;

    for (int i = 0; i < CountDic; i++) {
        if (Pos == Dictionary[i]->ShowPos()) {
            delete Dictionary[i];
            for (int j = i; j < CountDic - 1; j++) {
                Dictionary[j] = Dictionary[j + 1];
            }
            CountDic--;
            i--;
            if(flag == true) cout << "성공적으로 삭제하였습니다.\n";
        }
    }
    if(flag == false) cout << "해당 포지션의 정보가 없어 삭제된 항목이 없습니다.\n";

    system("cls");
}

void PrintAll()
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }

    system("cls");
    for (int i = 0; i < CountDic; i++) {
        Dictionary[i]->Show();
    }
    cout << "총 " << CountDic << "개의 항목이 있습니다.\n";
    cout << "\n\n";
}

void FindMaxHp()
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }

    double MaxHp{};
    int StoreNum{};

    system("cls");
    for (int i = 0; i < CountDic; i++) {
        if (MaxHp < Dictionary[i]->ShowHp()) {
            MaxHp = Dictionary[i]->ShowHp();
            StoreNum = i;
        }
    }

    cout << "Max HP Champion : ";
    Dictionary[StoreNum]->Show();
    cout << "\n\n";
}

void SortByHp()
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }

    quick_sort(0, CountDic - 1);    //CountDic은 데이터 끝 + 1을 가리키기에 -1을 하여 정렬.

    /*
    qsort(Dictionary, CountDic, sizeof(LOLDic*), [](const void* a, const void* b) {
        const LOLDic* ptrA = *static_cast<const LOLDic* const*>(a);
        const LOLDic* ptrB = *static_cast<const LOLDic* const*>(b);

        if (ptrA->ShowHp() > ptrB->ShowHp()) return -1; // 내림차순 정렬
        if (ptrA->ShowHp() < ptrB->ShowHp()) return 1;
        return 0;
        });
    */

    system("cls");
    cout << "내림차순 정렬되었습니다.\n\n";
}

void quick_sort(int start, int end) {
    if (start >= end) {
        return;
    }

    int pivot = start;	//피봇은 첫 번째 원소 
    int i{ pivot + 1 }, j{ end }; //i는 피봇 다음원소 j는 마지막 원소 
    LOLDic* temp;	

    while (i <= j) {
        //피봇 보다 큰 값 만날 때 까지
        while (i <= end && Dictionary[i]->ShowHp() >= Dictionary[pivot]->ShowHp()) {
            i++;
        }
        //피봇 보다 작은 값 만날 때 까지
        while (j > start && Dictionary[j]->ShowHp() <= Dictionary[pivot]->ShowHp()) {
            j--;
        }

        //위에서 계산된 i와 j가 만나거나 엇갈리면 종료
        if (i >= j) break;

        //두 원소 교환 
        temp = Dictionary[i];
        Dictionary[i] = Dictionary[j];
        Dictionary[j] = temp;
    }

    //피봇 정렬 완료
    temp = Dictionary[j];
    Dictionary[j] = Dictionary[pivot];
    Dictionary[pivot] = temp;

    quick_sort(start, j - 1);	//피봇 중심으로 왼쪽부분 분할 정렬
    quick_sort(j + 1, end);	    //피봇 중심으로 오른쪽부분 분할 정렬

}

void InSertTestData() {
    ifstream in("testdata.txt");
    if (!in.is_open()) {
        std::cerr << "Error opening testdata.txt" << std::endl;
        return;
    }

    string line;
    while (getline(in, line)) {
        size_t pos = 0;
        string token;
        string fields[6]; // name, hp, mp, speed, range, pos

        int index = 0;
        while ((pos = line.find("\t\t")) != string::npos && index < 5) {
            fields[index++] = line.substr(0, pos);
            line.erase(0, pos + 2); // "~~\t\t" 제거
        }
        fields[5] = line; // 마지막 데이터

        if (index == 5) { // 데이터가 올바르게 6개 저장되었는지 확인
            string name = fields[0], position = fields[5];
            int hp{ stoi(fields[1]) }, mp{ stoi(fields[2]) }, speed{ stoi(fields[3]) }, range{ stoi(fields[4]) };

            Dictionary[CountDic] = new LOLDic();
            Dictionary[CountDic]->InsertDic(name, hp, mp, speed, range, position);
            CountDic++;
        }
    }
    
    in.close();
}