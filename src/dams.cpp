#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <dams.h>

int main(int argc, char **argv) {
  std::string dicpath(""), query("");
  std::cerr << argc << std::endl;
  if (argc == 2) {
    query = argv[1];
    damswrapper::init();
  } else if (argc == 3) {
    query = argv[1];
    damswrapper::init(argv[2]);
  } else {
    std::cout << "Usage: main <query> [<dictionary path>]" << std::endl;
    std::cout << "default dictionary path = '" << damswrapper::default_dic_path() << "'" << std::endl;
    std::exit(0);
  }
	
  damswrapper::debugmode(false);
  int score;
  std::string tail;
  std::vector<damswrapper::Candidate> candidates;
  damswrapper::retrieve(score, tail, candidates, query);

  std::cout << "score=" << score << std::endl;
  std::cout << "tail=" << tail << std::endl;
  int cc = 0;
  for (std::vector<damswrapper::Candidate>::iterator it = candidates.begin(); it != candidates.end(); it++) {
    std::cout << "candidate[" << cc << "]:" << std::endl;
    for (damswrapper::Candidate::iterator itc = it->begin(); itc != it->end(); itc++) {
      std::cout << "  name=" << itc->get_name()
		<< ", level=" << itc->get_level()
		<< ", x=" << itc->get_x()
		<< ", y=" << itc->get_y() << std::endl;
    }
  }
  std::cout << "elapsed=" << damswrapper::elapsedtime() << std::endl;

  damswrapper::final();
  return 0;
}
