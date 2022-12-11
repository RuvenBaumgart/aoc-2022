#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cmath>


class Monkey{
    public:
        Monkey(){};
        Monkey(
                std::queue<unsigned long long> items,
                unsigned int id,
                unsigned int divisor, 
                unsigned int true_receiver, 
                unsigned int false_receiver,
                unsigned long long(*fn)(unsigned long long)
              ){
            this->items = items;
            this->id = id;
            this->divisor = divisor;
            this->true_receiver = true_receiver;
            this->false_receiver = false_receiver;
            this->change_worry_level = fn;
            turns = 0LL;
        };

        std::queue<unsigned long long> items;
        unsigned int id;
        unsigned long long turns;
        unsigned int divisor;
        unsigned int true_receiver;
        unsigned int false_receiver;
        unsigned long long (*change_worry_level)(unsigned long long);
        
        unsigned long long relief(long long x, long long num){
            return x % num;
        }
        bool test(unsigned long long x){
            return x % divisor == 0 ? true : false;
        }
};

#define ROUNDS 10000
//(a mod kn) mod n = a mod n


int main(int argc, char** argv){
    std::queue<unsigned long long> q0({50, 70, 54, 83, 52, 78});
    Monkey monkey0(q0, 0, 11, 2, 7,[](unsigned long long x){return x * 3;});
    
    std::queue<unsigned long long> q1({71, 52, 58, 60, 71});
    Monkey monkey1(q1, 1, 7, 0, 2, [](unsigned long long x){return x * x;});
    
    std::queue<unsigned long long>q2({66, 56, 56, 94, 60, 86, 73});
    Monkey monkey2(q2, 2, 3, 7, 5, [](unsigned long long x){return x  + 1; });

    std::queue<unsigned long long>q3({83, 99});
    Monkey monkey3(q3, 3, 5, 6, 4, [](unsigned long long x){return x + 8;});

    std::queue<unsigned long long>q4({98, 98, 79});
    Monkey monkey4(q4, 4, 17, 1, 0, [](unsigned long long x){return x + 3;});

    std::queue<unsigned long long>q5({76});
    Monkey monkey5(q5, 5, 13, 6, 3, [](unsigned long long x){return x + 4;});

    std::queue<unsigned long long>q6({52, 51, 84, 54});
    Monkey monkey6(q6, 6, 19, 4, 1, [](unsigned long long x){return x * 17;});

    std::queue<unsigned long long>q7({82, 86, 91, 79, 94, 92, 59, 94});
    Monkey monkey7(q7, 7, 2, 5, 3, [](unsigned long long x){return x + 7;});


    std::vector<Monkey> monkeys{monkey0, monkey1, monkey2, monkey3, monkey4, monkey5, monkey6, monkey7};
    
    long lcm = 1;
    for(int i = 0; i < monkeys.size(); i++){
        lcm *= monkeys[i].divisor; // since we have prime factors the lcm is the product of all primes
    }
    
    for(size_t i = 0; i < ROUNDS; i++){
        for(size_t j = 0; j < monkeys.size(); j++){
            while(!monkeys[j].items.empty()){
                unsigned long long current_item = monkeys[j].items.front();
                monkeys[j].items.pop();

                long long worry_level = monkeys[j].change_worry_level(current_item);
               
                worry_level = monkeys[j].relief(worry_level, lcm);
                
                if(monkeys[j].test(worry_level))
                    monkeys[monkeys[j].true_receiver].items.push(worry_level);
                else 
                    monkeys[monkeys[j].false_receiver].items.push(worry_level);
                
                monkeys[j].turns++;
            }
        }
    }

    std::sort(monkeys.begin(), monkeys.end(), [](const Monkey &ma,  const Monkey &mb){ return ma.turns > mb.turns;});
    long long result = monkeys[0].turns * monkeys[1].turns;
    std::cout << result << std::endl;
    return 0;
}
