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
 * Codesytle: This file is written in a sytle mainly based on Google C++ Style
 * Guide. As I use Clang-format to format my code, so the code style may be a
 * little bit strange sometimes, in that case I'll manually format the
 * code.What's sepecial is the comment:
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
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
static_assert(sizeof(int) == 4, "Expect int as a 32-bit integer.");
static_assert(sizeof(long long) == 8, "Expect long long as a 64-bit integer.");
namespace ICPCManager {
namespace BackEnd {
/**
 * Note that the team id is 1-based. The problem id is 0-based.
 */
const int kMaxTeamNumber = 10005;
std::unordered_map<std::string, int> team_name_to_id;
std::vector<std::string> team_id_to_name = {"nobody"};
int team_number = 0;
enum CompetitionStatusType { kNotStarted, kNormalRunning, kFrozen, kEnded };
enum SubmissionStatusType { kAC = 0, kWA = 1, kRE = 2, kTLE = 3 };
CompetitionStatusType competition_status = kNotStarted;
bool score_board_up_to_date = true;
int competition_duration_time;
int total_number_of_problems;
/**
 * @brief the definition of struct RawTeamDataType
 *
 * @details it stores the data of a team
 */
struct RawTeamDataType {
  std::string name;
  int id;
  int rank;
  struct SubmissionType {
    bool processed = false;
    SubmissionStatusType status;
    int submit_time;
  };
  std::set<int, std::greater<int>> unfreeze_pass_time;
  int query_status_index[4], query_problem_index[26],
      query_problem_status_index[26][4];
  bool is_frozen[26] = {false};
  std::vector<SubmissionStatusType> submissions;
  RawTeamDataType() { ; }
};
std::vector<RawTeamDataType> team_data = {RawTeamDataType()};
struct ScoreBoredElementType {
  int tid;
  int score;
  int penalty;
};
inline bool operator<(const ScoreBoredElementType &a,
                      const ScoreBoredElementType &b) {
  if (a.score != b.score) return a.score > b.score;
  if (a.penalty != b.penalty) return a.penalty < b.penalty;
  for (auto ita = team_data[a.tid].unfreeze_pass_time.begin(),
            itb = team_data[b.tid].unfreeze_pass_time.begin();
       ita != team_data[a.tid].unfreeze_pass_time.end() &&
       itb != team_data[b.tid].unfreeze_pass_time.end();
       ++ita, ++itb) {
    if (*ita != *itb) return *ita < *itb;
  }
  if (team_data[a.tid].name == team_data[b.tid].name)
    throw "teams in score bored should have distinctive names!";
  return team_data[a.tid].name < team_data[b.tid].name;
}
std::set<ScoreBoredElementType> score_board;
/**
 * @brief the definition of function AddTeam.
 * @param team_name the name of the team to be added.
 */
void AddTeam(const char *const team_name) {
  /*check if the name is duplicated*/
  if (team_name_to_id.find(team_name) != team_name_to_id.end()) {
    write("[Error]Add failed: duplicated team name.\n");
    return;
  }
  /*check if the competition has started*/
  if (competition_status != kNotStarted) {
    write("[Error]Add failed: competition has started.\n");
    return;
  }
  team_number++;
  team_name_to_id[team_name] = team_number;
  team_id_to_name.push_back(team_name);
  write("[Info]Team added.\n");
}
void StartCompetition(int duration_time, int problem_count) {
  if (competition_status != kNotStarted) {
    write("[Error]Start failed: competition has started.\n");
    return;
  }
  competition_duration_time = duration_time;
  total_number_of_problems = problem_count;
  competition_status = kNormalRunning;
  write("[Info]Competition starts.\n");
}
inline void Submit(char problem_name, char *team_name, char *submit_status,
                   int time) {
  ;
}
void FlushScoreBoard() { ; }
void FreezeScoreBoard() { competition_status = kFrozen; }
void ScrollScoreBoard() { ; }
void QueryRanking(char *team_name) { ; }
void QuerySubmission(char *team_name, char problem_name, char *submit_status) {
  ;
}
}  // namespace BackEnd

/**
 * @brief the namespace API is used to provide APIs for the main program.
 *
 * @details the APIs will call the functions in BackEnd to do the real work.
 * Then checking for unexpected error will be done here, thus the parameters
 * given to the functions in BackEnd are always valid.
 */
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
inline void StartCompetition(int duration_time, int problem_count) {
  BackEnd::StartCompetition(duration_time, problem_count);
}
inline void Submit(char problem_name, char *team_name, char *submit_status,
                   int time) {
  BackEnd::Submit(problem_name, team_name, submit_status, time);
}
inline void FlushScoreBoard() { BackEnd::FlushScoreBoard(); }
/**
 * @brief the definition of function FreezeScoreBoard
 */
inline void FreezeScoreBoard() { ICPCManager::BackEnd::FreezeScoreBoard(); }
inline void ScrollScoreBoard() { ICPCManager::BackEnd::ScrollScoreBoard(); }
inline void QueryRanking(char *team_name) {
  ICPCManager::BackEnd::QueryRanking(team_name);
}
inline void QuerySubmission(char *team_name, char problem_name,
                            char *submit_status) {
  ICPCManager::BackEnd::QuerySubmission(team_name, problem_name, submit_status);
}
/**
 * @brief this function is used to end the contest.
 */
void EndContest() {
  write("[Info]Competition ends.\n");
  exit(0);
}
/**
 * @brief the definition of function Excute.
 *
 * @details this function will analyze the command and call the corresponding
 * function in API.
 */
inline void Excute(const char *const command) {
  char command_name[1024];
  sscanf(command, "%s", command_name);
  if (strcmp(command_name, "ADDTEAM") == 0) {  // add a team
    char team_name[100];
    sscanf(command, "%*s%s", team_name);
    ICPCManager::API::AddTeam(team_name);
  } else if (strcmp(command_name, "START") == 0) {  // start the contest
    int duration_time, problem_count, paramater_count;
    paramater_count =
        sscanf(command, "%*s%*s%d%*s%d", &duration_time, &problem_count);
    if (paramater_count != 2) throw "Invalid paramaters.";
    ICPCManager::API::StartCompetition(duration_time, problem_count);
  } else if (strcmp(command_name, "SUBMIT") == 0) {  // submit a code
    char problem_name;
    char team_name[100];
    char submit_status[10];
    int time;
    sscanf(command, "%*s%c%*s%s%*s%s%*s%d", &problem_name, team_name,
           submit_status, &time);
    ICPCManager::API::Submit(problem_name, team_name, submit_status, time);
  } else if (strcmp(command_name, "FLUSH") == 0) {
    /*flush the score_board*/
    ICPCManager::API::FlushScoreBoard();
  } else if (strcmp(command_name, "FREEZE") == 0) {
    /*freeze the score_board*/
    ICPCManager::API::FreezeScoreBoard();
  } else if (strcmp(command_name, "SCROLL") == 0) {
    ICPCManager::API::ScrollScoreBoard();
  } else if (strcmp(command_name, "QUERY_RANKING") == 0) {
    char team_name[100];
    sscanf(command, "%*s%s", team_name);
    ICPCManager::API::QueryRanking(team_name);
  } else if (strcmp(command_name, "QUERY_SUBMISSION") == 0) {
    char team_name[100];
    char problem_name;
    char status[10];
    sscanf(command, "%*s%s%*s%*s%c%*s%*s%s", team_name, &problem_name, status);
    ICPCManager::API::QuerySubmission(team_name, problem_name, status);
  } else if (strcmp(command_name, "END") == 0)  // END
  {
    ICPCManager::API::EndContest();
  } else
    throw "Unknown command.";
}
}  // namespace API
}  // namespace ICPCManager
int main() {
  char command[1024];
  try {
    while (true) {
      readline(command);
      ICPCManager::API::Excute(command);
    }
  } catch (const char *msg) {
    fprintf(stderr, "\e[7m\e[31m[Unexpected Error] %s\e[0m\n", msg);
    exit(1);
  }
  return 0;
}