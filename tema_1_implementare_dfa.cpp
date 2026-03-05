#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

/*DFA + NFA + lambda-NFA + bonus minimizer on lambda-NFA -> DFA
fisier pe fiecare linie cu DFA=(Q, sigma, q0, functie, stari finale)

input.txt:
    sir de stari
    sir de litere
    starea initiala
    starea finala
    cuvintele
    relatiile: stare 1 litera stare 2
*/



class Graph_DFA{
    std::vector<std::string> Q;
    std::vector<std::string> lit;
    std::string initial_q;
    std::unordered_set<std::string> finalQ;
    std::vector<std::string> cuv;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> map;


    public:
        Graph_DFA(const std::vector<std::string> &Q, const std::vector<std::string> &lit, const std::string &initial_q,
            const std::unordered_set<std::string> &finalQ, const std::vector<std::string> &cuv,
            const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> &map){
                this -> Q = Q;
                this -> lit = lit;
                this -> initial_q = initial_q;
                this -> finalQ = finalQ;
                this -> cuv = cuv;
                this -> map = map;
            }
        void afisare(){
            std::cout<<"Multimea starilor: ";
            for(auto i:Q){
                std::cout<<i<<" ";
            }
            std::cout<<'\n';

            std::cout<<"Multimea literelor: ";
            for(auto i:lit){
                std::cout<<i<<" ";
            }
            std::cout<<'\n';

            std::cout<<"Starea initiala: ";
            std::cout<<initial_q;
            std::cout<<'\n';

            std::cout<<"Multimea starilor finale: ";
            for(auto i:finalQ){
                std::cout<<i<<" ";
            }
            std::cout<<'\n';

            std::cout<<"Multimea cuvintelor: ";
            for(auto i:cuv){
                std::cout<<i<<" ";
            }
            std::cout<<'\n';

            std::cout<<"Relatiile: "<<'\n';
            for(auto [key_stare1, val]:map){
                for(auto [key_litera, stare2]:val){
                    std::cout<<key_stare1<<": "<<key_litera<<": "<<stare2;
                    std::cout<<'\n';
                }
            }
        }
        void parcurgere(){
            std::string stare_curenta = initial_q;
            int pozitie; 
            for(std::string cuvant:cuv){
                std::cout<<"Verificarea cuvantului: "<<cuvant;
                std::cout<<'\n';
                pozitie = 0;
                bool ended = true;
                while(pozitie < cuvant.size()){
                    std::string str_poz = std::string(1, cuvant[pozitie]); // din char in string prin constructor
                    std::cout<<'\t';
                    if (map[stare_curenta].find(str_poz) != map[stare_curenta].end()){
                        std::cout<<cuvant.substr(pozitie)<<"|"<<stare_curenta<<" -> "<<
                        cuvant.substr(pozitie+1)<<"|"<<map[stare_curenta][str_poz]<<'\n';
                        stare_curenta = map[stare_curenta][str_poz];
                        pozitie++;
                    }
                    else{
                        ended = false;
                        pozitie = cuvant.size();
                    }
                }
                if (finalQ.find(stare_curenta) != finalQ.end() && ended){
                    std::cout<<'\t'<<"Cuvantul: "<<cuvant<<" este VALID";
                }
                else{
                    std::cout<<'\t'<<"Cuvantul: "<<cuvant<<" este INVALID";
                }
                std::cout<<'\n';
            }
        }
};

void initializare_DFA(){
    std::cout<<"Numele fisierului de input: ";
    std::string file_name;
    std::cin>>file_name;
    std::ifstream fin(file_name);

    std::vector<std::string> Q;
    std::vector<std::string> lit;
    std::string initial_q;
    std::unordered_set<std::string> finalQ;
    std::vector<std::string> cuv;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> map;

    std::string aux;
    std::string temp;
    std::string stare1_aux;
    std::string litera_aux;
    std::string stare2_aux;
    // citire stari
    std::getline(fin, temp);
    std::stringstream check(temp);
    while(getline(check, aux, ' ')){
        Q.push_back(aux);
    }
    check.clear();
    // citire litere
    std::getline(fin, temp);
    check.str(temp);
    while(getline(check, aux, ' ')){
        lit.push_back(aux);
    }
    check.clear();

    // citire stare initiala
    std::getline(fin, initial_q);

    // citire stari finale
    std::getline(fin, temp);
    check.str(temp);
    while(getline(check, aux, ' ')){
        finalQ.insert(aux);
    }
    check.clear();

    // citire cuvinte
    std::getline(fin, temp);
    check.str(temp);
    while(getline(check, aux, ' ')){
        cuv.push_back(aux);
    }
    check.clear();

    // citire tranzitii
    while(!fin.eof()){
        std::getline(fin, temp);
        check.str(temp);
        // starea1 = cheie
        getline(check, stare1_aux, ' ');
        // litera + stare2 = valoare
        getline(check, litera_aux, ' ');
        getline(check, stare2_aux, ' ');
        map[stare1_aux][litera_aux] = stare2_aux;
        check.clear();
    }

    fin.close();
    Graph_DFA Graph(Q, lit, initial_q, finalQ, cuv, map);
    Graph.afisare();
    Graph.parcurgere();
}

int main(){
    initializare_DFA();
    return 0;
}