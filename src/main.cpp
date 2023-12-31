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
#include <cstdio>
#define unlikely(x) __builtin_expect(!!(x), 0)
struct char_reader {
  FILE *f;
  char *buf, *p1, *p2;
  int size;
  char_reader(FILE *fin, int bufsize = 1 << 16) {
    f = fin;
    size = bufsize;
    p1 = p2 = 0;
    buf = new char[size];
  }
  ~char_reader() { delete[] buf; }
  inline int operator()() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, size, f), p1 == p2)
               ? EOF
               : *p1++;
  }
};
struct char_writer {
  FILE *f;
  char *buf, *p, *end;
  int size;
  char_writer(FILE *fout, int bufsize = 1 << 16) {
    f = fout;
    size = bufsize;
    buf = new char[size];
    p = buf;
    end = buf + bufsize;
  }
  ~char_writer() {
    fwrite(buf, p - buf, 1, f);
    delete[] buf;
  }
  inline char operator()(char ch) {
    if (unlikely(end == p)) {
      fwrite(buf, end - buf, 1, f);
      p = buf;
    }
    return *p++ = ch;
  }
};
char_reader gch(stdin);
char_writer wch(stdout);
template <typename T>
inline int read(T &t) {
  bool f = false;
  int ch;
  while (ch = gch(), !((ch >= '0' && ch <= '9') || ch == '-')) {
    if (ch == EOF) return 0;
  }
  t = 0;
  if (ch == '-') f = true, ch = gch();
  t = ch ^ 48;
  while (ch = gch(), ch >= '0' && ch <= '9')
    t = (t << 3) + (t << 1) + (ch ^ 48);
  if (f) t = -t;
  return 1;
}
inline int read(char &c) {
  c = 0;
  int ch;
  while (ch = gch(), (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')) {
    if (ch == EOF) return 0;
  }
  c = ch;
  return 1;
}
inline int read(char *s) {
  int ch;
  while (ch = gch(), (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')) {
    if (ch == EOF) return 0;
  }
  *s++ = ch;
  while (ch = gch(),
         !(ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') && ch != EOF)
    *s++ = ch;
  *s++ = 0;
  return 1;
}
inline int read(const char *s) { return read((char *)s); }
inline int readline(char *s) {
  int ch;
  while (ch = gch(), (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')) {
    if (ch == EOF) return 0;
  }
  *s++ = ch;
  while (ch = gch(), !(ch == '\n' || ch == '\r') && ch != EOF) *s++ = ch;
  *s++ = 0;
  return 1;
}
inline int readline(const char *s) { return readline((char *)s); }
template <typename T>
inline void write(T t) {
  int stk[20], cnt = 0;
  if (t == 0) {
    wch('0');
    return;
  }
  if (t < 0) {
    wch('-');
    t = -t;
  }
  while (t > 0) {
    stk[cnt++] = t % 10;
    t /= 10;
  }
  while (cnt) wch(stk[--cnt] + '0');
}
inline void write(char t) { wch(t); }
inline void write(char *s) {
  while (*s) wch(*s++);
}
inline void write(const char *s) { write((char *)s); }
#if __cplusplus >= 201103L
template <typename T, typename... Args>
inline int read(T &t, Args &...args) {
  return read(t) + read(args...);
}
template <typename T, typename... Args>
inline void write(T t, Args... args) {
  write(t);
  write(args...);
}
#else
template <typename A_t, typename B_t>
inline int read(A_t &a, B_t &b) {
  return read(a) + read(b);
}
template <typename A_t, typename B_t, typename C_t>
inline int read(A_t &a, B_t &b, C_t &c) {
  return read(a) + read(b) + read(c);
}
template <typename A_t, typename B_t, typename C_t, typename D_t>
inline int read(A_t &a, B_t &b, C_t &c, D_t &d) {
  return read(a) + read(b) + read(c) + read(d);
}
template <typename A_t, typename B_t>
inline void write(A_t a, B_t b) {
  write(a);
  write(b);
}
template <typename A_t, typename B_t, typename C_t>
inline void write(A_t a, B_t b, C_t c) {
  write(a);
  write(b);
  write(c);
}
template <typename A_t, typename B_t, typename C_t, typename D_t>
inline void write(A_t a, B_t b, C_t c, D_t d) {
  write(a);
  write(b);
  write(c);
  write(d);
}
#endif
// end of fast-read libarary
// #define DebugOn
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
std::string StatusType2Text[4] = {"Accepted", "Wrong_Answer", "Runtime_Error",
                                  "Time_Limit_Exceed"};
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
  char problem_name;
  SubmissionType() {}
  SubmissionType(SubmissionStatusType status, int submit_time,
                 char problem_name)
      : status(status), submit_time(submit_time), problem_name(problem_name) {}
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
  int name_rank;
  // std::multiset<int, std::greater<int>> pass_time_before_freeze;
  int pass_time_before_freeze[27] = {kIntInf, kIntInf, kIntInf, kIntInf,
                                     kIntInf, kIntInf, kIntInf, kIntInf,
                                     kIntInf, kIntInf, kIntInf, kIntInf,
                                     kIntInf, kIntInf, kIntInf, kIntInf,
                                     kIntInf, kIntInf, kIntInf, kIntInf,
                                     kIntInf, kIntInf, kIntInf, kIntInf,
                                     kIntInf, kIntInf, kIntInf};
  int query_status_index[4], query_problem_index[26],
      query_problem_status_index[26][4];
  // as index in submissions are 0 based, so we use -1 to indicate that the team
  // has not submitted a problem satisfying the query condition.
  bool is_frozen[26] = {false};
  bool already_passed[26] = {false};
  bool already_passed_before_block[26] = {false};
  bool acceptence_tracked[26] = {false};
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
  if (a.tid == b.tid) return false;
  if (a.score != b.score) return a.score > b.score;
  if (a.penalty != b.penalty) return a.penalty < b.penalty;
  auto &TDA = team_data[a.tid];
  auto &TDB = team_data[b.tid];
  auto &ta = TDA.pass_time_before_freeze;
  auto &tb = TDB.pass_time_before_freeze;
  int p = 0;
  if (ta[p + 16] == kIntInf) p += 17;
  if (ta[p + 8] == kIntInf) p += 9;
  for (; p < 27; p++) {
    if (ta[p] ^ tb[p]) return ta[p] < tb[p];
  }
  return TDA.name_rank < TDB.name_rank;
}
__gnu_pbds::tree<ScoreBoredElementType, __gnu_pbds::null_type,
                 std::less<ScoreBoredElementType>, __gnu_pbds::rb_tree_tag>
    score_board;
std::vector<int> teams_to_be_updated;
std::vector<bool> teams_not_latest;
std::vector<ScoreBoredElementType> value_in_score_board;
std::vector<int> scroll_cursor;
/**
 * @brief the definition of function AddTeam.
 * @param team_name the name of the team to be added.
 */
void AddTeam(const char *const team_name) {
  /*check if the competition has started*/
  if (competition_status != kNotStarted) {
    write("[Error]Add failed: competition has started.\n");
    return;
  }
  /*check if the name is duplicated*/
  if (team_name_to_id.find(team_name) != team_name_to_id.end()) {
    write("[Error]Add failed: duplicated team name.\n");
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
  write("[Info]Add successfully.\n");
}
void StartCompetition(int duration_time, int problem_count) {
  if (competition_status != kNotStarted) {
    write("[Error]Start failed: competition has started.\n");
    return;
  }
  competition_duration_time = duration_time;
  total_number_of_problems = problem_count;
  competition_status = kNormalRunning;
  /*init the name_rank*/
  std::vector<std::pair<std::string, int>> name_rank;
  name_rank.reserve(team_number);
  for (int i = 1; i <= team_number; i++)
    name_rank.push_back(std::make_pair(team_data[i].name, i));
  std::sort(name_rank.begin(), name_rank.end());
  for (int i = 0; i < team_number; i++)
    team_data[name_rank[i].second].name_rank = i;
  /*init the score board*/
  value_in_score_board.resize(team_number + 1);
  for (int i = 1; i <= team_number; i++) {
    score_board.insert(ScoreBoredElementType(i, 0, 0));
    value_in_score_board[i] = ScoreBoredElementType(i, 0, 0);
#ifdef DebugOn
    if (score_board.find(value_in_score_board[i]) == score_board.end())
      throw "cannot find tid in score_board immediately after insert in func StartCompetition";
#endif
  }
  int cnt = 0;
  auto ite = score_board.end();
  for (auto it = score_board.begin(); it != ite; ++it) {
    team_data[it->tid].rank = ++cnt;
  }
  teams_to_be_updated.reserve(team_number + 1);
  teams_not_latest.resize(team_number + 1);
  scroll_cursor.resize(team_number + 1);
  write("[Info]Competition starts.\n");
}
inline void Submit(char problem_name, char *team_name,
                   const char *submit_status, int time) {
  int team_id = team_name_to_id[team_name];
  SubmissionStatusType status = SubmitStatusParser[submit_status];
  SubmissionType record = SubmissionType(status, time, problem_name);
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
        if (teams_not_latest[team_id] == false)
          teams_to_be_updated.push_back(team_id);
        teams_not_latest[team_id] = true;
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
/**
 * @brief the definition of function Submit.
 *
 * @details this function will add data that should be available to user but
 * hasn't been added to the score board to the score board. Note that the two
 * parameters are used when the function was called by ScrollScoreBoard() to
 * delicately control its behavior.
 */
void FlushScoreBoard(bool show_info = true, bool rebuild = true) {
  if (rebuild) {
    for (int i = 0; i < teams_to_be_updated.size(); i++) {
      int tid = teams_to_be_updated[i];
      int score = 0, penalty = 0;
      std::vector<int> new_problems_accepted;
      for (int j = 0; j < total_number_of_problems; j++) {
        if (team_data[tid].already_passed_before_block[j]) {
          penalty += team_data[tid].first_pass_time[j] +
                     team_data[tid].try_times_before_pass[j] * 20;
          score++;
          if (team_data[tid].acceptence_tracked[j] == false) {
            new_problems_accepted.push_back(j);
            team_data[tid].acceptence_tracked[j] = true;
          }
        }
      }
#ifdef DebugOn
      if (score_board.find(value_in_score_board[tid]) == score_board.end()) {
        char *error_message = new char[1005];
        sprintf(error_message,
                "cannot find tid in score_board immediately before erase in "
                "func FlushScoreBoard, tid=%d , score=%d , penalty=%d, "
                "previous tid=%d\n",
                tid, value_in_score_board[tid].score,
                value_in_score_board[tid].penalty,
                value_in_score_board[tid].tid);
        throw error_message;
      }
#endif
      score_board.erase(value_in_score_board[tid]);
      for (int j : new_problems_accepted) {
        auto &pass_time_before_freeze = team_data[tid].pass_time_before_freeze;
        int p = 0;
        int v = team_data[tid].first_pass_time[j];
        for (; p < 26; p++) {
          if (pass_time_before_freeze[p + 1] <= v) {
            pass_time_before_freeze[p] = v;
            break;
          }
          pass_time_before_freeze[p] = pass_time_before_freeze[p + 1];
        }
        if (p == 26) pass_time_before_freeze[26] = v;
      }
      score_board.insert(ScoreBoredElementType(tid, score, penalty));
      value_in_score_board[tid] = ScoreBoredElementType(tid, score, penalty);
      teams_not_latest[tid] = false;
    }
    teams_to_be_updated.clear();
#ifdef DebugOn
    if (score_board.size() != team_number)
      throw "score_board.size()!=team_number";
#endif
  }
  int cnt = 0;
  auto ite = score_board.end();
  for (auto it = score_board.begin(); it != ite; ++it) {
    team_data[it->tid].rank = ++cnt;
  }
  if (show_info) write("[Info]Flush scoreboard.\n");
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
  auto ite = score_board.end();
  for (auto it = score_board.begin(); it != ite; ++it) {
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
#ifdef DebugOn
void CheckDataAfterScroll() {
  for (int i = 1; i <= team_number; i++)
    for (int j = 0; j < total_number_of_problems; j++)
      if (team_data[i].is_frozen[j]) throw "has frozen problem after scroll!";
}
#endif
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
  for (int i = 1; i <= team_number; i++) scroll_cursor[i] = 0;
  while (true) {
    /**
     * this `while (true)` is the main loop, for each time it will try to
     * unfroze at most one problem
     */
    auto nxt = it;
    bool is_first = false;
    bool frozen_found = false;
    if (it == score_board.begin()) is_first = true;
    if (!is_first) --nxt;
    auto nval = *nxt;
    // When a frozen problem is found, as the iterator may be effectless, we
    // need to use nval to determine where the pointer should be moved to. By
    // default, the pointer will be moved to the next team.
    for (int &i = scroll_cursor[it->tid]; i < total_number_of_problems; i++) {
      if (team_data[it->tid].is_frozen[i]) {
        /*start processing a frozen problem*/
        frozen_found = true;
        team_data[it->tid].is_frozen[i] = false;
        team_data[it->tid].already_passed_before_block[i] |=
            team_data[it->tid].already_passed[i];
        team_data[it->tid].try_times_before_pass_before_block[i] =
            team_data[it->tid].try_times_before_pass[i];
        team_data[it->tid].submissions_during_block[i] = 0;
#ifdef DebugOn
        if (team_data[it->tid].already_passed[i] !=
            (team_data[it->tid].first_pass_time[i] < kIntInf))
          throw "already_passed not equal to first_pass_time < kIntInf";
#endif
        if (team_data[it->tid].already_passed[i]) {
          /*now we began to process a newly accepted problem*/
          int score = it->score + 1;
          if (teams_not_latest[it->tid] == false)
            teams_to_be_updated.push_back(it->tid);
          teams_not_latest[it->tid] = true;
          int penalty = it->penalty + team_data[it->tid].first_pass_time[i] +
                        20 * team_data[it->tid].try_times_before_pass[i];
          int tid = it->tid;
          score_board.erase(it);
          team_data[tid].acceptence_tracked[i] = true;
          auto &pass_time_before_freeze =
              team_data[tid].pass_time_before_freeze;
          int p = 0;
          int v = team_data[tid].first_pass_time[i];
          for (; p < 26; p++) {
            if (pass_time_before_freeze[p + 1] <= v) {
              pass_time_before_freeze[p] = v;
              break;
            }
            pass_time_before_freeze[p] = pass_time_before_freeze[p + 1];
          }
          if (p == 26) pass_time_before_freeze[26] = v;
          score_board.insert(ScoreBoredElementType(tid, score, penalty));
          value_in_score_board[tid] =
              ScoreBoredElementType(tid, score, penalty);
#ifdef DebugOn
          if (score_board.find(value_in_score_board[tid]) == score_board.end())
            throw "cannot find tid in score_board immediately after insert in func ScrollScoreBoard";
#endif
          if (!is_first && ScoreBoredElementType(tid, score, penalty) < nval) {
            /*1. the team replace another team*/
            auto newp =
                score_board.find(ScoreBoredElementType(tid, score, penalty));
            newp++;
            write(team_id_to_name[tid].c_str(), ' ',
                  team_id_to_name[newp->tid].c_str(), ' ', score, ' ', penalty,
                  '\n');
            // In this case nval remains its default value
          } else
            nval = ScoreBoredElementType(tid, score, penalty);
          // 2. has new passed problem but the rank is not changed, current team
          // may have another frozen problem, so nval changed accordingly
        } else
          nval = *it;
        // 3. no new passed problem and the rank is not changed, current team
        // may have another problem, so nval changed accordingly
        /**
         * When current team has no frozen problems, this whole piece of code
         * won't be executed. And the last three sentences of the main loop will
         * be executed to move pointer to next team or end scrolling.
         */
        it = score_board.find(nval);
        if (it == score_board.end()) goto finish_scroll;
        // special process to avoid mistakes when current team ranks first(it
        // seems useless)
        /**
         * This piece of code has been executed means current round of scrolling
         * has done. So we need to execute `goto next_round;` and move the
         * pointer to start next round or end scrolling.
         */
        goto next_round;
      }
    }
    it = nxt;  // the defualt position to move the pointer to when no frozen
               // problem is found
    /** When current team has no frozen problems, the pointer will be moved to
     * the default position. The `goto next_round;` setence skips `it=nxt;` to
     * allow the pointer remains the position caculated in the last round.
     */
  next_round:;
    if (is_first && !frozen_found) break;
    // special process (this is surely useful)
  }
finish_scroll:;
  competition_status = kNormalRunning;
  FlushScoreBoard(false, false);
#ifdef DebugOn
  CheckDataAfterScroll();
#endif
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
  if (team_name_to_id.find(team_name) == team_name_to_id.end()) {
    write("[Error]Query submission failed: cannot find the team.\n");
    return;
  }
  write("[Info]Complete query submission.\n");
  bool found = false;
  SubmissionType res;
  int tid = team_name_to_id[team_name];
  // clang-format off
  if (strcmp(problem_name, "ALL") == 0) {
    if (strcmp(submit_status, "ALL") == 0) {
      if (team_data[tid].submissions.size() > 0) {
        res = team_data[tid].submissions[team_data[tid].submissions.size() - 1];
        found = true;
      }
    } else {
      if (team_data[tid]
              .query_status_index[SubmitStatusParser[submit_status]] != -1) {
        res =
            team_data[tid].submissions
                [team_data[tid].query_status_index[SubmitStatusParser[submit_status]]];
        found = true;
      }
    }
  } else {
    if (strcmp(submit_status, "ALL") == 0) {
      if (team_data[tid].query_problem_index[problem_name[0] - 'A'] != -1) {
        res = team_data[tid].submissions
                  [team_data[tid].query_problem_index[problem_name[0] - 'A']];
        found = true;
      }
    } else {
      if (team_data[tid]
              .query_problem_status_index[problem_name[0] - 'A']
                                         [SubmitStatusParser[submit_status]] != -1)
      {
        res = team_data[tid]
              .submissions[team_data[tid].query_problem_status_index
                                           [problem_name[0] - 'A']
                                           [SubmitStatusParser[submit_status]]];
        found = true;
      }
    }
  }
  // clang-format on
  if (!found) {
    write("Cannot find any submission.\n");
    return;
  }
  write(team_name, ' ', res.problem_name, ' ',
        StatusType2Text[res.status].c_str(), ' ', res.submit_time, "\n");
}
#ifdef DebugOn
void PrintStatus() {
  for (int i = 1; i <= team_number; i++) {
    fprintf(stderr, "team %d: %s\n", i, team_data[i].name.c_str());
    /*value_in_score_board*/
    fprintf(stderr, "value_in_score_board: %d %d %d\n",
            value_in_score_board[i].tid, value_in_score_board[i].score,
            value_in_score_board[i].penalty);
  }
  /*score_board*/
  fprintf(stderr, "score_board:\n");
  for (auto it = score_board.begin(); it != score_board.end(); ++it) {
    fprintf(stderr, "%d %d %d\n", it->tid, it->score, it->penalty);
  }
}
void CheckAccordanceBetweenScoreBoardAndValueInScoreBoard() {
  for (int i = 1; i <= team_number; i++) {
    if (score_board.find(value_in_score_board[i]) == score_board.end()) {
      PrintStatus();
      throw "cannot find tid in score_board immediately after insert in func CheckAccordanceBetweenScoreBoardAndValueInScoreBoard";
    }
  }
}
#endif
}  // namespace BackEnd

/**
 * @brief the namespace API is used to provide APIs for the main program.
 *
 * @details the APIs will call the functions in BackEnd to do the real work.
 * Then checking for unexpected error will be done here, thus the parameters
 * given to the functions in BackEnd are always valid.
 */
namespace API {
void AddTeam(const char *const team_name) {
  int len = strlen(team_name);
#ifdef DebugOn
  if (len > 20) throw "Team name too long.";
  for (int i = 0; i < len; i++)
    if (!(team_name[i] >= 'a' && team_name[i] <= 'z' ||
          team_name[i] >= 'A' && team_name[i] <= 'Z' ||
          team_name[i] >= '0' && team_name[i] <= '9' || team_name[i] == '_'))
      throw "Team name contains invalid characters.";
      // All checks passed.
#endif
  BackEnd::AddTeam(team_name);
}
inline void StartCompetition(int duration_time, int problem_count) {
  BackEnd::StartCompetition(duration_time, problem_count);
}
inline void Submit(char problem_name, char *team_name, char *submit_status,
                   int time) {
#ifdef DebugOn
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
#endif
  BackEnd::Submit(problem_name, team_name, submit_status, time);
}
inline void FlushScoreBoard() {
#ifdef DebugOn
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
#endif
  BackEnd::FlushScoreBoard();
}
/**
 * @brief the definition of function FreezeScoreBoard
 */
inline void FreezeScoreBoard() {
#ifdef DebugOn
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
#endif
  ICPCManager::BackEnd::FreezeScoreBoard();
}
inline void ScrollScoreBoard() {
#ifdef DebugOn
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
#endif
  ICPCManager::BackEnd::ScrollScoreBoard();
}
inline void QueryRanking(char *team_name) {
#ifdef DebugOn
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
#endif
  ICPCManager::BackEnd::QueryRanking(team_name);
}
inline void QuerySubmission(char *team_name, char *problem_name,
                            char *submit_status) {
#ifdef DebugOn
  if (BackEnd::competition_status == BackEnd::kNotStarted)
    throw "Competition hasn't started yet.";
#endif
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
      /*add a team*/
      char team_name[100];
      sscanf(command, "%*s%s", team_name);
      ICPCManager::API::AddTeam(team_name);
      break;
    }
    case ICPCManager::BackEnd::kSTART: {
      /*start the contest a initialize some data*/
      int duration_time, problem_count, paramater_count;
      paramater_count =
          sscanf(command, "%*s%*s%d%*s%d", &duration_time, &problem_count);
#ifdef DebugOn
      if (paramater_count != 2) throw "Invalid paramaters.";
#endif
      ICPCManager::API::StartCompetition(duration_time, problem_count);
      break;
    }
    case ICPCManager::BackEnd::kSUBMIT: {
      /*do a submission*/
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
      /*scroll the board*/
      ICPCManager::API::ScrollScoreBoard();
      break;
    }
    case ICPCManager::BackEnd::kQUERY_RANKING: {
      /*query a team's rank*/
      char team_name[100];
      sscanf(command, "%*s%s", team_name);
      ICPCManager::API::QueryRanking(team_name);
      break;
    }
    case ICPCManager::BackEnd::kQUERY_SUBMISSION: {
      /*query a team's submission*/
      char team_name[100];
      char problem_name[10];
      char status[20];
      sscanf(command, "QUERY_SUBMISSION %s WHERE PROBLEM=%s AND STATUS=%s",
             team_name, problem_name, status);
      ICPCManager::API::QuerySubmission(team_name, problem_name, status);
      break;
    }
    case ICPCManager::BackEnd::kEND: {
      /*stop the contest*/
      ICPCManager::API::EndContest();
      break;
    }
    default: {
#ifdef DebugOn
      throw "Unknown command.";
#endif
    }
  }
#ifdef DebugOn
  if (BackEnd::competition_status != BackEnd::kNotStarted)
    BackEnd::CheckAccordanceBetweenScoreBoardAndValueInScoreBoard();
#endif
}
}  // namespace API
}  // namespace ICPCManager
int main() {
  char command[1024];
#ifdef DebugOn
  try {
#endif
    while (true) {
      readline(command);
      ICPCManager::API::Excute(command);
    }
#ifdef DebugOn
  } catch (const char *msg) {
    fprintf(stderr, "\e[7m\e[31m[Unexpected Error] %s\e[0m\n", msg);
    exit(1);
  }
#endif
  return 0;
}