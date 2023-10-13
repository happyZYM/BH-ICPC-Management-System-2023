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
const char *current_command;  // only for debug
namespace ICPCManager {
namespace BackEnd {
/**
 * Note that the team id is 1-based. The problem id is 0-based.
 */
const int kMaxTeamNumber = 10005;
const int kIntInf = 0x3f3f3f3f;
std::unordered_map<std::string, int> team_name_to_id;
std::vector<std::string> team_id_to_name = {"nobody"};
enum CompetitionStatusType { kNotStarted, kNormalRunning, kBlocked, kEnded };
enum SubmissionStatusType { kAC = 0, kWA = 1, kRE = 2, kTLE = 3 };
enum CommandType {
  kADDTEAM,
  kSTART,
  kSUBMIT,
  kFLUSH,
  kFREEZE,
  kSCROLL,
  kQUERY_RANKING,
  kQUERY_SUBMISSION,
  kEND
};
std::unordered_map<std::string, SubmissionStatusType> SubmitStatusParser = {
    {"Accepted", kAC},
    {"Wrong_Answer", kWA},
    {"Runtime_Error", kRE},
    {"Time_Limit_Exceed", kTLE}};
std::unordered_map<std::string, CommandType> CommandParser = {
    {"ADDTEAM", kADDTEAM},
    {"START", kSTART},
    {"SUBMIT", kSUBMIT},
    {"FLUSH", kFLUSH},
    {"FREEZE", kFREEZE},
    {"SCROLL", kSCROLL},
    {"QUERY_RANKING", kQUERY_RANKING},
    {"QUERY_SUBMISSION", kQUERY_SUBMISSION},
    {"END", kEND}};
CompetitionStatusType competition_status = kNotStarted;
bool score_board_up_to_date = true;
int competition_duration_time;
int total_number_of_problems;
int team_number = 0;
struct SubmissionType {
  bool synced_to_score_board = false;
  SubmissionStatusType status;
  int submit_time;
  SubmissionType() {}
  SubmissionType(SubmissionStatusType status, int submit_time)
      : status(status), submit_time(submit_time) {}
};
/**
 * @brief the definition of struct RawTeamDataType
 *
 * @details it stores the data of a team
 */
struct RawTeamDataType {
  std::string name;
  int id;
  int rank;
  std::set<int, std::greater<int>> pass_time_before_freeze;
  int query_status_index[4], query_problem_index[26],
      query_problem_status_index[26][4];
  // as index in submissions are 0 based, so we use -1 to indicate that the team
  // has not submitted a problem satisfying the query condition.
  bool is_frozen[26] = {false};
  bool already_passed[26] = {false};
  bool already_passed_before_block[26] = {false};
  int first_pass_time[26] = {kIntInf, kIntInf, kIntInf, kIntInf, kIntInf,
                             kIntInf, kIntInf, kIntInf, kIntInf, kIntInf,
                             kIntInf, kIntInf, kIntInf, kIntInf, kIntInf,
                             kIntInf, kIntInf, kIntInf, kIntInf, kIntInf,
                             kIntInf, kIntInf, kIntInf, kIntInf, kIntInf,
                             kIntInf};
  int try_times_before_pass[26] = {0};
  int try_times_before_pass_before_block[26] = {0};
  int submissions_during_block[26] = {0};
  std::vector<SubmissionType> submissions;
  RawTeamDataType() { ; }
};
std::vector<RawTeamDataType> team_data = {RawTeamDataType()};
// warning: team_data[0] has no meaning
struct ScoreBoredElementType {
  int tid;
  int score;
  int penalty;
  ScoreBoredElementType() {}
  ScoreBoredElementType(int tid, int score, int penalty)
      : tid(tid), score(score), penalty(penalty) {}
};
inline bool operator<(const ScoreBoredElementType &a,
                      const ScoreBoredElementType &b) {
  if (a.score != b.score) return a.score > b.score;
  if (a.penalty != b.penalty) return a.penalty < b.penalty;
  for (auto ita = team_data[a.tid].pass_time_before_freeze.begin(),
            itb = team_data[b.tid].pass_time_before_freeze.begin();
       ita != team_data[a.tid].pass_time_before_freeze.end() &&
       itb != team_data[b.tid].pass_time_before_freeze.end();
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
  team_data.push_back(RawTeamDataType());
  team_data[team_number].name = team_name;
  team_data[team_number].id = team_number;
  /*update three index to -1*/
  for (int i = 0; i < 4; i++) team_data[team_number].query_status_index[i] = -1;
  for (int i = 0; i < 26; i++) {
    team_data[team_number].query_problem_index[i] = -1;
    for (int j = 0; j < 4; j++)
      team_data[team_number].query_problem_status_index[i][j] = -1;
  }
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
  /*init the score board*/
  for (int i = 1; i <= team_number; i++) {
    score_board.insert(ScoreBoredElementType(i, 0, 0));
  }
  int cnt = 0;
  for (auto it = score_board.begin(); it != score_board.end(); ++it) {
    team_data[it->tid].rank = ++cnt;
  }
  write("[Info]Competition starts.\n");
}
inline void Submit(char problem_name, char *team_name,
                   const char *submit_status, int time) {
  int team_id = team_name_to_id[team_name];
  SubmissionStatusType status = SubmitStatusParser[submit_status];
  SubmissionType record = SubmissionType(status, time);
  team_data[team_id].submissions.push_back(record);
  team_data[team_id].query_problem_index[problem_name - 'A'] =
      team_data[team_id].submissions.size() - 1;
  team_data[team_id].query_problem_status_index[problem_name - 'A'][status] =
      team_data[team_id].submissions.size() - 1;
  team_data[team_id].query_status_index[status] =
      team_data[team_id].submissions.size() - 1;
  if (team_data[team_id].already_passed_before_block[problem_name - 'A'] == 0 &&
      competition_status == kBlocked) {
    team_data[team_id].is_frozen[problem_name - 'A'] = true;
    team_data[team_id].submissions_during_block[problem_name - 'A']++;
  }
  switch (status) {
    case kAC: {
      if (team_data[team_id].already_passed[problem_name - 'A'] == false) {
        team_data[team_id].first_pass_time[problem_name - 'A'] = time;
      }
      team_data[team_id].already_passed[problem_name - 'A'] = true;
      if (competition_status == kNormalRunning) {
        team_data[team_id].already_passed_before_block[problem_name - 'A'] =
            true;
        team_data[team_id].pass_time_before_freeze.insert(time);
      }
      break;
    }
    case kRE:
    case kWA:
    case kTLE: {
      if (team_data[team_id].already_passed[problem_name - 'A'] == false) {
        team_data[team_id].try_times_before_pass[problem_name - 'A']++;
        if (competition_status != kBlocked) {
          team_data[team_id]
              .try_times_before_pass_before_block[problem_name - 'A']++;
        }
      }
      break;
    }
  }
}
void FlushScoreBoard(bool show_info=true) {
  score_board.clear();
  for (int i = 1; i <= team_number; i++) {
    int score = 0, penalty = 0;
    for (int j = 0; j < total_number_of_problems; j++) {
      if (team_data[i].already_passed_before_block[j]) {
        penalty += team_data[i].first_pass_time[j] +
                   team_data[i].try_times_before_pass[j] * 20;
        score++;
      }
    }
    score_board.insert(ScoreBoredElementType(i, score, penalty));
  }
  int cnt = 0;
  for (auto it = score_board.begin(); it != score_board.end(); ++it) {
    team_data[it->tid].rank = ++cnt;
  }
  if(show_info) write("[Info]Flush scoreboard.\n");
}
void FreezeScoreBoard() {
  if (competition_status == kBlocked) {
    write("[Error]Freeze failed: scoreboard has been frozen.\n");
    return;
  }
  competition_status = kBlocked;
  write("[Info]Freeze scoreboard.\n");
}
void PrintScoreBoard() {
  for (auto it = score_board.begin(); it != score_board.end(); ++it) {
    write(team_data[it->tid].name.c_str());
    write(' ', team_data[it->tid].rank);
    write(' ', it->score);
    write(' ', it->penalty);
    for (int i = 0; i < total_number_of_problems; i++) {
      write(' ');
      if (team_data[it->tid].is_frozen[i] == false) {
        if (team_data[it->tid].already_passed_before_block[i]) {
          write('+');
          if (team_data[it->tid].try_times_before_pass[i] > 0)
            write(team_data[it->tid].try_times_before_pass[i]);
        } else {
          if (team_data[it->tid].try_times_before_pass[i] > 0) {
            write('-', team_data[it->tid].try_times_before_pass[i]);
          } else
            write('.');
        }
      } else {
        int x = team_data[it->tid].try_times_before_pass_before_block[i];
        if (x != 0) write('-');
        write(x, '/', team_data[it->tid].submissions_during_block[i]);
      }
    }
    write('\n');
  }
}
void ScrollScoreBoard() {
  if (competition_status != kBlocked) {
    write("[Error]Scroll failed: scoreboard has not been frozen.\n");
    return;
  }
  write("[Info]Scroll scoreboard.\n");
  FlushScoreBoard(false);
  PrintScoreBoard();
  auto it = score_board.end();
  --it;
  while (true) {
    auto nxt = it;
    bool is_first = false;
    bool frozen_found = false;
    if (it == score_board.begin()) is_first = true;
    --nxt;
    auto nval = *nxt;
    // fprintf(stderr,"%d\n",it->tid);
    for (int i = 0; i < total_number_of_problems; i++) {
      if (team_data[it->tid].is_frozen[i]) {
        frozen_found = true;
        team_data[it->tid].is_frozen[i] = false;
        team_data[it->tid].already_passed_before_block[i] =
            team_data[it->tid].already_passed[i];
        team_data[it->tid].try_times_before_pass_before_block[i] =
            team_data[it->tid].try_times_before_pass[i];
        team_data[it->tid].submissions_during_block[i] = 0;
        if (team_data[it->tid].first_pass_time[i] < kIntInf) {
          int score = it->score + 1;
          team_data[it->tid].pass_time_before_freeze.insert(
              team_data[it->tid].first_pass_time[i]);
          int penalty = it->penalty + team_data[it->tid].first_pass_time[i] +
                        20 * team_data[it->tid].try_times_before_pass[i];
          score_board.erase(it);
          score_board.insert(ScoreBoredElementType(it->tid, score, penalty));
        }
        it = score_board.find(nval);
        if (it == score_board.end()) goto finish_scroll;
        goto next_round;
      }
    }
    it = nxt;
  next_round:;
    if (is_first && !frozen_found) break;
  }
finish_scroll:;
  competition_status = kNormalRunning;
  FlushScoreBoard(false);
  PrintScoreBoard();
}
void QueryRanking(char *team_name) {
  if (team_name_to_id.find(team_name) == team_name_to_id.end()) {
    write("[Error]Query ranking failed: cannot find the team.\n");
    return;
  }
  write("[Info]Complete query ranking.\n");
  if (competition_status == kBlocked)
    write(
        "[Warning]Scoreboard is frozen. The ranking may be inaccurate until it "
        "were scrolled.\n");
  write(team_name, " NOW AT RANKING ",
        team_data[team_name_to_id[team_name]].rank, "\n");
}
void QuerySubmission(char *team_name, char *problem_name, char *submit_status) {
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
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
  if (ICPCManager::BackEnd::team_name_to_id.find(team_name) ==
      ICPCManager::BackEnd::team_name_to_id.end()) {
    char *str = new char[1000];
    sprintf(str,
            "Team not found when excuting SUBMIT %c BY %s WITH %s AT "
            "%d\ncurrent command is [%s]\n",
            problem_name, team_name, submit_status, time, current_command);
    throw str;
  }
  BackEnd::Submit(problem_name, team_name, submit_status, time);
}
inline void FlushScoreBoard() {
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
  BackEnd::FlushScoreBoard();
}
/**
 * @brief the definition of function FreezeScoreBoard
 */
inline void FreezeScoreBoard() {
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
  ICPCManager::BackEnd::FreezeScoreBoard();
}
inline void ScrollScoreBoard() {
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
  ICPCManager::BackEnd::ScrollScoreBoard();
}
inline void QueryRanking(char *team_name) {
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
  ICPCManager::BackEnd::QueryRanking(team_name);
}
inline void QuerySubmission(char *team_name, char *problem_name,
                            char *submit_status) {
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
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
  current_command = command;
  sscanf(command, "%s", command_name);
  ICPCManager::BackEnd::CommandType command_type =
      ICPCManager::BackEnd::CommandParser[command_name];
  switch (command_type) {
    case ICPCManager::BackEnd::kADDTEAM: {
      char team_name[100];
      sscanf(command, "%*s%s", team_name);
      ICPCManager::API::AddTeam(team_name);
      break;
    }
    case ICPCManager::BackEnd::kSTART: {
      int duration_time, problem_count, paramater_count;
      paramater_count =
          sscanf(command, "%*s%*s%d%*s%d", &duration_time, &problem_count);
      if (paramater_count != 2) throw "Invalid paramaters.";
      ICPCManager::API::StartCompetition(duration_time, problem_count);
      break;
    }
    case ICPCManager::BackEnd::kSUBMIT: {
      char problem_name[10];
      char team_name[100];
      char submit_status[20];
      int time;
      sscanf(command, "%*s%s%*s%s%*s%s%*s%d", problem_name, team_name,
             submit_status, &time);
      ICPCManager::API::Submit(problem_name[0], team_name, submit_status, time);
      break;
    }
    case ICPCManager::BackEnd::kFLUSH: {
      /*flush the score_board*/
      ICPCManager::API::FlushScoreBoard();
      break;
    }
    case ICPCManager::BackEnd::kFREEZE: {
      /*freeze the score_board*/
      ICPCManager::API::FreezeScoreBoard();
      break;
    }
    case ICPCManager::BackEnd::kSCROLL: {
      ICPCManager::API::ScrollScoreBoard();
      break;
    }
    case ICPCManager::BackEnd::kQUERY_RANKING: {
      char team_name[100];
      sscanf(command, "%*s%s", team_name);
      ICPCManager::API::QueryRanking(team_name);
      break;
    }
    case ICPCManager::BackEnd::kQUERY_SUBMISSION: {
      char team_name[100];
      char problem_name[10];
      char status[20];
      sscanf(command, "%*s%s%*s%*s%s%*s%*s%s", team_name, problem_name, status);
      ICPCManager::API::QuerySubmission(team_name, problem_name, status);
      break;
    }
    case ICPCManager::BackEnd::kEND: {
      ICPCManager::API::EndContest();
      break;
    }
    default: {
      throw "Unknown command.";
    }
  }
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