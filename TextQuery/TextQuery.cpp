#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<set>

using namespace std;

class Text{
    private:
        vector<string> content;//store text lines
        map< string, set<int> > word_with_lines;//store words and their line numbers
        string search_word;
        set<int> result_line_nums;
        ifstream &open_file(ifstream &in, const string file);
    public:
        Text(){}
        void init(const string &file);
        void query(const string &word);
//        void text_line(set<int> lines);
        void print_result();
};
ifstream & Text::open_file(ifstream &in, string file){
    in.close();
    in.clear();
    in.open(file.c_str());
    return in;
}
void Text::init(const string &file){
    ifstream text;
    if(!open_file(text, file)){
       cerr << "OPEN FAILURE！"<< endl;;    
       return;
    }
    string line, word;
    int line_num(0);
    while(getline(text,line)){
        content.push_back(line);
        istringstream stream(line);
        while(stream >> word){
            word_with_lines[word].insert(line_num);
        }
        ++line_num;
    }
    return;
}

void Text::query(const string &word) {
    search_word = word;
    if(word_with_lines.find(word) != word_with_lines.end())
        result_line_nums = word_with_lines[word];
    return;
}
void Text::print_result(){
    cout << search_word << " occurs " << result_line_nums.size() << " times\n";
    for(set<int>::iterator iter = result_line_nums.begin(); iter !=  result_line_nums.end(); ++iter){
        cout << "( line " << *iter + 1 << " ) " << content[*iter] << endl;
    }
}

int main(int arc, char *argv[]){
    if(arc < 2){
        cerr << "NO INPUT FILE!" << endl;
        return -1;
    }
    Text text;
    text.init(argv[1]);
    while(true){
        cout << "Enter Your Word to look for, or q to quit: ";
        string search_word;
        cin >> search_word;
        if(search_word == "q")
            break;
        text.query(search_word);
        text.print_result();
    }
    return 0;
}
