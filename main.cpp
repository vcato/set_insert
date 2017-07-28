#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <set>
#include <iostream>


using std::vector;
using std::string;
using std::cerr;
using std::set;
using RandomEngine = std::mt19937;
using Clock = std::chrono::system_clock;


static char randomCharacter(RandomEngine &engine)
{
  return 'a'+std::uniform_int_distribution<int>(0,25)(engine);
}


static string randomString(RandomEngine &random_engine)
{
  string s;
  s.reserve(40);

  for (int i=0; i!=40; ++i) {
    s.push_back(randomCharacter(random_engine));
  }

  return s;
}


static void showTimeBetween(Clock::time_point a,Clock::time_point b)
{
  std::chrono::duration<double> duration_in_seconds = b-a;
  cerr << "Time: " << duration_in_seconds.count() << "\n";
}


static vector<string> generateRandomStrings(int count)
{
  std::mt19937 engine(1);
  vector<string> random_strings;

  cerr << "Generating strings\n";

  for (int i=0; i!=count; ++i) {
    random_strings.push_back(randomString(engine));
    if (i%100000==0) {
      cerr << ".";
    }
  }

  cerr << "\n";

  return random_strings;
}


static void
  insertStringsInto(
    set<string> &string_set,
    const vector<string> &strings
  )
{
  cerr << "Inserting strings\n";

  for (int i=0, n=strings.size(); i!=n; ++i) {
    string_set.insert(strings[i]);
    if (i%100000==0) {
      cerr << ".";
    }
  }

  cerr << "\n";
}


int main()
{
  int count = 30000000;

  Clock::time_point start_time = Clock::now();
  vector<string> random_strings = generateRandomStrings(count);
  Clock::time_point time_after_generating = Clock::now();
  showTimeBetween(start_time,time_after_generating);
  set<string> string_set;
  insertStringsInto(string_set,random_strings);
  Clock::time_point time_after_inserting = Clock::now();
  showTimeBetween(time_after_generating,time_after_inserting);
}
