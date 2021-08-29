#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int con;
class Notepad
{
vector<string> allContent;
stack<vector<string>> undoStack;
stack<vector<string>> redoStack;
vector<string> split(string, char);
vector<string> buffer;
public:
Notepad(string);
void display();
bool display(int, int);
bool insert(int, string);
bool Delete(int);
bool Delete(int, int);
bool copy(int, int);
bool paste(int);
bool undo();
bool redo();
};
Notepad::Notepad(string text)
{
allContent = split(text, '\n');
}
vector<string> Notepad::split(string text, char delim)
{
vector<string> result;
auto pos = text.find(delim);
auto i = 0;
while(pos != string::npos)
{
result.push_back(text.substr(i, pos-i));
i = ++pos;
pos = text.find(delim, pos);
}
result.push_back(text.substr(i, text.length()));
return result;
}
void Notepad::display()
{
for(string s: allContent)
cout << s << "\n";
}
bool Notepad::display(int n, int m)
{
if (static_cast<size_t>(n) > allContent.size())
{
cout << " The value of n exceeds number of lines in the file\n";
return false;
}
if (static_cast<size_t>(m) > allContent.size())
{
cout << "The value of m exceeds number of lines in the file\n";
return false;
}
if (n > m)
{
cout << "The value of n exceeds the value of m\n";
return false;
}
for(vector<string>::iterator iter = allContent.begin() + n -
1; iter != allContent.begin() + m; ++iter)
{
cout << *iter << endl;
}
return true;
}
bool Notepad::insert(int n, string text)
{
if (static_cast<size_t>(n) > allContent.size())
{
cout << "The value of n exceeds number of lines in the file\n";
return false;
}
undoStack.push(allContent);
string *content = &(*(allContent.begin() + n - 1));
*content += text;
return true;
}
bool Notepad::Delete(int n)
{
if (static_cast<size_t>(n) > allContent.size())
{
cout << "The value of n exceeds number of lines in the file\n";
return false;
}
undoStack.push(allContent);
allContent.erase(allContent.begin() + n - 1);
return true;
}
bool Notepad::Delete(int n, int m)
{
if (static_cast<size_t>(n) > allContent.size())
{
cout << "The value of n exceeds number of lines in the file\n";
return false;
}
if (static_cast<size_t>(m) > allContent.size())
{
cout << "The value of m exceeds number of lines in the file\n";
return false;
}
if (n > m)
{
cout << "The value of n exceeds the value of m\n";
return false;
}
undoStack.push(allContent);
allContent.erase(allContent.begin() + n - 1,
allContent.begin() + m);
return true;
}
bool Notepad::copy(int n, int m)
{
if (static_cast<size_t>(n) > allContent.size())
{
cout << "The value of n exceeds number of lines in the file"<<endl;
return false;
}
if (static_cast<size_t>(m) > allContent.size())
{
cout << "The value of m exceeds number of lines in the file"<<endl;;
return false;
}
if (n > m)
{
cout << "The value of n exceeds the value of m\n"<<endl;
return false;
}
for(vector<string>::iterator iter = allContent.begin() + n -
1; iter != allContent.begin() + m; ++iter)
{
buffer.push_back(*iter);
}
return true;
}
bool Notepad::paste(int n)
{
if (static_cast<size_t>(n) > allContent.size())
{
cout << "The value of n exceeds number of lines in the file"<<endl;
return false;
}
undoStack.push(allContent);
allContent.insert(allContent.begin() + n - 1,
buffer.begin(), buffer.end());
return true;
}
bool Notepad::undo()
{
if(undoStack.empty())
{
cout << "Nothing to undo!\n";
return false;
}
redoStack.push(allContent);
allContent = undoStack.top();
undoStack.pop();
return true;
}
bool Notepad::redo()
{
if(redoStack.empty())
{
cout << "Nothing to redo!\n";
return false;
}
undoStack.push(allContent);
allContent = redoStack.top();
redoStack.pop();
return true;
}
int main()
{
 cout<<"\t\t\t\t TEXT EDITOR"<<endl;
 cout<<"DISPLAYNG lines "<<endl;
 Notepad notepad("THIS PROJECT IS MADE BY\nASHITA\nAGRAWAL");
notepad.display();
cout <<endl<<endl;
cout<<"\t\t\t\t\t CHOICES"<<endl;
cout<<"\t\t\t\t2.DISPLAY SPECIFIC LINES"<<endl;
cout<<"\t\t\t\t3.TO INSERT AT SPECIFIC LINE N"<<endl;
cout<<"\t\t\t\t4.DELETE THE SPECIFIC LINE "<<endl;
cout<<"\t\t\t\t5.DELETE THE SPECIFIC LINE FROM N TO M"<<endl;
cout<<"\t\t\t\t6.COPY CONTENTS FROM LINE N TO M TO CLIPBOARD"<<endl;
cout<<"\t\t\t\t7.PASTE CONTENST FROM CLIPBOARD TO LINE N "<<endl;
cout<<"\t\t\t\t8.UNDO THE LAST COMMAND"<<endl;
cout<<"\t\t\t\t9.REDO THE LAST COMMAND"<<endl;
int ch;
do
{
cout <<" ENTER YOUR CHOICE "<<endl;
cin>>ch;
switch (ch)
{
case 2 :
{cout << "ENTER THE VALUE OF M AND N (FROM WHICH LINE WHICH TO WHICH U WWANT TO PRINT)"<<endl;
int n ,m;
 cin>>n>>m;
notepad.display(n,m);
break;
}
case 3:
{
 cout << "ENTER THE NEW DATA U WANT TO INSERT ANDAT WHICH LINE "<<endl;
string a;
int b;
cin>>a>>b;
cout << "** Inserting "<< a<< "to the"<< b <<"line**"<<endl;
notepad.insert(b,a);
notepad.display();
break;
}
case 4:
 {cout<<"enter the line u want to delete"<<endl;
 int a ;cin >>a;
 cout <<"** Deleting "<<a<<"line **"<<endl;
notepad.Delete(a);
notepad.display();
break;
 }
 case 5:
{cout<<"enter the line u want to delete"<<endl;
 int a,b ;cin>>a>>b;
cout << "** deletion of lines" << a<<"to" <<b
<<"**"<<endl;
notepad.Delete(a,b);
notepad.display();
break;
}
case 6:
 {
int a,b;cin>>a>>b;
cout << "** Copying lines"<< a<<" to"<< b<<endl;
notepad.copy(1,2);
break;
 }
 case 7:
 {
 cout <<"ENTER THE LINE AT WHICH U WANT TO PASTE"<<endl;
 int c ;
 cin>>c;
 notepad.paste(c);
notepad.display();
break;
 }
case 8:
{cout << "** Undoing last move **\n";
notepad.undo();
notepad.display();
break;
}
case 9:
{cout << "** Redoing last move **\n";
notepad.redo();
notepad.display();
break;
}
}
cout<<"IF U WANT TO CONTINUE PRESS 1 ELSE 0"<<endl;
cin>>con;
cout <<" *******************************************************************************************************"<<endl;
}while(con==1);
return 0;
}
