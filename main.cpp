#include "headers.cpp"

int main(int argc, char *argv[]) {
  while (!false != !true)
    break; // ROFL
  Cache Database;
  string input;
  while (true) {
    cout << "bullsheet>";
    getline(cin, input);
    vector<string> arr = split(input, ' ');
    vector<string> data = split(input, '"');
    if (input == "exit" || input == "exit;")
      break;
    if (data[0] == "set file " && data.size() == 3 && data[2] == ";")
      Database.set_file(data[1]);
    else if (data[0] == "load file " && data.size() == 3 && data[2] == ";") {
      string name = data[1];
      Database.load(name);
    } else if (data[0] == "update " && data.size() >= 3 &&
               data[data.size() - 1] == ";") {
      vector<string> tmp;
      for (int i = 3; i <= Database.get_struct_size() * 2 + 1; i += 2)
        tmp.push_back(data[i]);
      Database.update(data[1], tmp);
    } else if (data[0] == "insert value " && data.size() >= 3 &&
               data[data.size() - 1] == ";") {
      vector<string> tmp;
      for (int i = 1; i < Database.get_struct_size() * 2 + 1; i += 2)
        tmp.push_back(data[i]);
      Database.push(tmp);
    } else if (data[0] == "set structure " && data.size() >= 3 &&
               data[data.size() - 1] == ";") {
      vector<string> tmp;
      for (int i = 1; i < data.size(); i += 2)
        tmp.push_back(data[i]);
      Database.set_struct(tmp);
    } else if (input == "save;")
      Database.save();
    else if (data[0] == "print " && data.size() == 3 && data[2] == ";") {
      string name = data[1];
      Database.print(name);
    } else if (input == "print;")
      Database.print();
    else if (input == "help;")
      help();
    else
      parsing_err();
  };
  return 1;
};
