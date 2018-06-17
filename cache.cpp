struct el {
  int id;
  vector<string> data;
};

class Cache {
private:
  class Node;
  Node *first;
  Node *last;
  int length;
  int str_size;
  vector<string> structure;
  string get_list(vector<el> &list);
  string get_list_print(vector<el> &list);
  el get_el(string str);
  string get_table();

public:
  string filename;
  Cache();
  ~Cache();
  void save();
  void push(vector<string> data);
  void set_struct(vector<string> data);
  void print();
  void print(string value);
  int get_struct_size();
  void load(string filename);
  void set_file(string str);
  void update(string name, vector<string> &data);
};

class Cache::Node {
public:
  int id;
  vector<el> data;
  Node *prev;
  Node *next;
  Node(int id) { this->id = id; };
  Node(){};
};

Cache::Cache() {
  str_size = 0;
  length = 1;
  first = new Node();
  last = first;
};

Cache::~Cache() {
  for (int i = length - 2; i > 0; i--) {
    last = last->prev;
    length--;
    delete last->next;
  }
  delete first;
  length = 0;
};

void Cache::push(vector<string> data) {
  if (str_size == 0) {
    cout << "Database structure is not set, type help for more info" << endl;
    return;
  }
  int id = get_first_id(data[0]);
  el newEl = {get_second_id(data[0]), data};
  Node *tmp = first;
  for (int i = 0; i < length - 1; i++) {
    if (id == tmp->id) {
      tmp->data.push_back(newEl);
      return;
    }
    tmp = tmp->next;
  }
  if (length == 1) {
    first->id = id;
    first->data.push_back(newEl);
    length++;
    return;
  } else {
    Node *newNode = new Node(id);
    newNode->data.push_back(newEl);
    newNode->prev = last;
    last->next = newNode;
    last = newNode;
    length++;
    return;
  }
};

string Cache::get_list(vector<el> &list) {
  string result;
  for (int i = 0; i < list.size(); i++) {
    result = result + to_string(list[i].id);
    result = result + " | " + join(list[i].data, ' ') + '\t';
  }
  return result;
};

string Cache::get_list_print(vector<el> &list) {
  string result = "| " + join(list[0].data, " | ");
  for (int i = 1; i < list.size(); i++)
    result = result + "\n| " + join(list[i].data, " | ");
  return result;
};

void Cache::print() {
  if (str_size == 0) {
    cout << "Database is empty\n";
    return;
  }
  Node *tmp = first;
  cout << "| ";
  for (int i = 0; i < str_size; i++)
    cout << structure[i] + " | ";
  for (int i = 0; i < length - 1; i++) {
    cout << '\n' << this->get_list_print(tmp->data);
    tmp = tmp->next;
  }
  cout << '\n';
};

void Cache::print(string value) {
  int id = get_first_id(value);
  Node *result = first;
  if (first->id == id) result = first;
  else
    for (int i = 0; i < length - 1; i++) {
      if (result->id == id) break;
      result = result->next;
    }
  cout << this->get_list_print(result->data) << '\n';
};

el Cache::get_el(string str) {
  int id = get_first_id(str);
  Node *result = nullptr;
  if (first->id == id) result = first;
  else {
    Node *tmp = first;
    for (int i = 0; i < length - 1; i++) {
      if (tmp->id == id) break;
      tmp = tmp->next;
    }
    result = tmp;
  }
  if (result != nullptr) {
    int second_id = get_second_id(str);
    for (int i = 0; i < result->data.size(); i++)
      if (result->data[i].id == second_id) return result->data[i];
  }
  vector<string> res;
  return el{-1, res};
};

string Cache::get_table() {
  string result = structure[0];
  for (int i = 1; i < str_size; i++)
    result = result + " | " + structure[i];
  result += '\n';
  Node *tmp = first;
  for (int i = 0; i < length - 1; i++) {
    result = result + to_string(tmp->id);
    result = result + '\t' + this->get_list(tmp->data) + '\n';
    tmp = tmp->next;
  }
  return result;
};

void Cache::save() {
  if (str_size == 0) {
    cout << "Database structure is not set, type help for more info" << endl;
    return;
  }
  fstream file;
  file.open(filename, ios::out);
  if (file.is_open()) {
    file << get_table();
    file.close();
  }
};

void Cache::set_file(string str) { filename = str + ".bullsheet"; };

int Cache::get_struct_size() { return str_size; };

void Cache::set_struct(vector<string> data) {
  structure = data;
  str_size = data.size();
};

void Cache::load(string filename) {
  ifstream file;
  file.open(filename, ios::in);
  string st;
  getline(file, st);
  vector<string> tmp_struct;
  vector<string> tmp = split(st, '|');
  tmp_struct.push_back(split(tmp[0], ' ')[0]);
  for (int i = 1; i < tmp.size(); i++)
    tmp_struct.push_back(split(tmp[i], ' ')[1]);
  if (tmp_struct.size() == 0) cout << "Wrong or damaged file.";
  set_struct(tmp_struct);
  if (file.is_open()) {
    this->filename = filename;
    string data;
    do {
      getline(file, data);
      vector<string> arr = split(data, '|');
      for (int i = 1; i < arr.size(); i++) {
        vector<string> el = split(arr[i], ' ');
        vector<string> tmp;
        for (int i = 1; i <= get_struct_size(); i++) {
          string temp = el[i];
          tmp.push_back(temp);
        }
        push(tmp);
      }
    } while (!data.empty());
  } else cout << "Can't read file" << filename << endl;
};

void Cache::update(string name, vector<string> &data) {
  int id = get_first_id(name);
  Node *result = nullptr;
  if (first->id == id) result = first;
  else {
    Node *tmp = first;
    for (int i = 0; i < length - 1; i++) {
      if (tmp->id == id) break;
      tmp = tmp->next;
    };
    result = tmp;
  };
  for (int i = 0; i < result->data.size(); i++)
    if (result->data[i].data[0] == name)
      result->data.erase(result->data.begin() + i);
  push(data);
};
