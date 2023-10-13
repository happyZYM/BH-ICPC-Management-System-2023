/**
 * @file main.cpp
 *
 * @brief this is the main code of ICPC-Management-System
 *
 * @details In the function main(), the program will read the input data and
 * call the APIs. Then the APIs will call the detailed functions to do the real
 * work. Note that expected error will be processed according to the document
 * and unexpected error will be reported by exceptions. This program won't use
 * assert() to check things but will use static_assert() to check some basic
 * things.
 *
 * @codesytle This file is written in a sytle mainly based on Google C++ Style
 * Guide. What's sepecial is the comment:
 * 1. Multi-line comments are always before the code they comment on.
 * Usually the code they comment on is a complex procedure,like the definition
 * of a function,a class or a variable with complex operation. If a multi-line
 * comment is in one line, it will start with "/*" instead of "/**",otherwise it
 * will start with "/**" and in the format of Doxygen.
 * 2. Single-line comments are always after the code they comment on.
 * Usually they are in the same line with the code they comment on,but sometimes
 * they may come in the next lines. single-line comments shouldn't exceed 3
 * lines as they are intended to be short and easy to understand.
 * 3. Temporary disabled code will be marked with "//" in the front of each
 * 4. Some comments have special meanings,like "//TODO", "//FIXME", "//XXX","//
 * clang-format off" and "// clang-format on". They are not controlled by the
 * previous rules.
 *
 * As I use Clang-format to format my code, so the code style may be a little
 * bit strange sometimes, in the case I'll manually format the code.
 */
/**
 * the following is a mannually embedded fast-read libarary.
 */
// clang-format off
#include<cstdio>
#define unlikely(x)     __builtin_expect(!!(x), 0)
struct char_reader
{
	FILE* f; char *buf,*p1,*p2; int size;
	char_reader(FILE* fin,int bufsize=1<<16) { f=fin; size=bufsize; p1=p2=0; buf=new char[size]; }
	~char_reader() { delete []buf; }
	inline int operator()() { return p1==p2&&(p2=(p1=buf)+fread(buf,1,size,f),p1==p2)?EOF:*p1++; }
};
struct char_writer
{
	FILE* f; char *buf,*p,*end; int size;
	char_writer(FILE* fout,int bufsize=1<<16) { f=fout; size=bufsize; buf=new char[size]; p=buf; end=buf+bufsize; }
	~char_writer() { fwrite(buf,p-buf,1,f); delete []buf; }
	inline char operator()(char ch)
	{
		if(unlikely(end==p)) { fwrite(buf,end-buf,1,f); p=buf; }
		return *p++=ch;
	}
};
char_reader gch(stdin);
char_writer wch(stdout);
template<typename T> inline int read(T& t)
{
	bool f=false; int ch; while(ch=gch(),!((ch>='0'&&ch<='9')||ch=='-')) { if(ch==EOF) return 0; }
	t=0;
	if(ch=='-') f=true,ch=gch(); t=ch^48; while(ch=gch(),ch>='0'&&ch<='9') t=(t<<3)+(t<<1)+(ch^48);
	if(f) t=-t;
	return 1;
}
inline int read(char &c)
{
	c=0; int ch; while(ch=gch(),(ch==' '||ch=='\n'||ch=='\r'||ch=='\t')) { if(ch==EOF) return 0; } c=ch;
	return 1;
}
inline int read(char *s)
{
	int ch; while(ch=gch(),(ch==' '||ch=='\n'||ch=='\r'||ch=='\t')) { if(ch==EOF) return 0; }
	*s++=ch; while(ch=gch(),!(ch==' '||ch=='\n'||ch=='\r'||ch=='\t')&&ch!=EOF) *s++=ch; *s++=0;
	return 1;
} inline int read(const char *s) { return read((char*)s); }
inline int readline(char *s)
{
	int ch; while(ch=gch(),(ch==' '||ch=='\n'||ch=='\r'||ch=='\t')) { if(ch==EOF) return 0; }
	*s++=ch; while(ch=gch(),!(ch=='\n'||ch=='\r')&&ch!=EOF) *s++=ch; *s++=0;
	return 1;
} inline int readline(const char *s) { return readline((char*)s); }
template<typename T> inline void write(T t)
{
	int stk[20],cnt=0;
	if(t==0) { wch('0'); return; } if(t<0) { wch('-'); t=-t; }
	while(t>0) { stk[cnt++]=t%10; t/=10; } while(cnt) wch(stk[--cnt]+'0');
}
inline void write(char t) { wch(t); }
inline void write(char *s) { while(*s) wch(*s++); } inline void write(const char *s) { write((char*)s); }
#if __cplusplus >= 201103L
template<typename T,typename... Args> inline int read(T& t,Args&... args) { return read(t)+read(args...); }
template<typename T,typename... Args> inline void write(T t,Args... args) { write(t); write(args...); }
#else
template<typename A_t,typename B_t> inline int read(A_t &a,B_t &b) { return read(a)+read(b); }
template<typename A_t,typename B_t,typename C_t> inline int read(A_t &a,B_t &b,C_t &c) { return read(a)+read(b)+read(c); }
template<typename A_t,typename B_t,typename C_t,typename D_t> inline int read(A_t &a,B_t &b,C_t &c,D_t &d) { return read(a)+read(b)+read(c)+read(d); }
template<typename A_t,typename B_t> inline void write(A_t a,B_t b) { write(a); write(b); }
template<typename A_t,typename B_t,typename C_t> inline void write(A_t a,B_t b,C_t c) { write(a); write(b); write(c); }
template<typename A_t,typename B_t,typename C_t,typename D_t> inline void write(A_t a,B_t b,C_t c,D_t d) { write(a); write(b); write(c); write(d); }
#endif
// clang-format on
// end of fast-read libarary
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
static_assert(sizeof(int) == 4, "Expected 32-bit integer.");
static_assert(sizeof(long long) == 8, "Expected 64-bit integer.");
namespace ICPCManager {
namespace BackEnd {
const int kMaxTeamNumber = 10005;
std::unordered_map<std::string, int> team_name_to_id;
std::vector<std::string> team_id_to_name = {"nobody"};
int team_number = 0;
bool competition_on = false;
/**
 * @brief the definition of function AddTeam.
 * @param team_name the name of the team to be added.
 */
void AddTeam(const char *const team_name) {
  /*check if the name is duplicated*/
  if (team_name_to_id.find(team_name) != team_name_to_id.end())
  {
    write("[Error]Add failed: duplicated team name.\n");
    return;
  }
  /*check if the competition has started*/
  if (competition_on)
  {
    write("[Error]Add failed: competition has started.\n");
    return;
  }
  team_number++;
  team_name_to_id[team_name] = team_number;
  team_id_to_name.push_back(team_name);
  write("[Info]Team added.\n");
}
}  // namespace BackEnd
namespace API {
/**
 * @brief this function is used to add a team.
 */
void AddTeam(const char *const team_name) {
  int len = strlen(team_name);
  if (len > 20) throw "Team name too long.";
  for (int i = 0; i < len; i++)
    if (!(team_name[i] >= 'a' && team_name[i] <= 'z' ||
          team_name[i] >= 'A' && team_name[i] <= 'Z' ||
          team_name[i] >= '0' && team_name[i] <= '9' || team_name[i] == '_'))
      throw "Team name contains invalid characters.";
  // All checks passed.
  BackEnd::AddTeam(team_name);
}
/**
 * @brief this function is used to end the contest.
 */
void EndContest() {
  write("[Info]Competition ends.\n");
  exit(0);
}
}  // namespace API
}  // namespace ICPCManager
inline void Excute(const char *const command) {
  char command_name[1024];
  sscanf(command, "%s", command_name);
  if (strcmp(command_name, "ADDTEAM") == 0) {  // add a team
    char team_name[100];
    sscanf(command, "%*s%s", team_name);
    ICPCManager::API::AddTeam(team_name);
  } else if (strcmp(command_name, "START") == 0) {  // start the contest
    ;
  } else if (strcmp(command_name, "SUBMIT") == 0) {  // submit a code
    ;
  } else if (strcmp(command_name, "FLUSH") == 0) {  // flush the
    ;
  } else if (strcmp(command_name, "FREEZE") == 0) {
    ;
  } else if (strcmp(command_name, "SCROLL") == 0) {
    ;
  } else if (strcmp(command_name, "QUERY_RANKING") == 0) {
    ;
  } else if (strcmp(command_name, "QUERY_SUBMISSION") == 0) {
    ;
  } else if (strcmp(command_name, "END") == 0)  // END
  {
    ICPCManager::API::EndContest();
  } else
    throw "Unknown command.";
}
int main() {
  char command[1024];
  try {
    while (true) {
      readline(command);
      Excute(command);
    }
  } catch (const char *msg) {
    fprintf(stderr, "\e[7m\e[31m[Unexpected Error] %s\e[0m\n", msg);
    exit(1);
  }
  return 0;
}