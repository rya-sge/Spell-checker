//
// Created by super on 05/12/2020.
//

namespace std {
    template<>
    struct hash<Person> {
        std::size_t operator()(const Person& p) {
            using std::size_t;
            using std::hash;
            using std::string;
            size_t hashval = 17;
            hashval = 31*hashval + hash<string>()(p.name);
            hashval = 31*hashval + hash<string>()(p.firstname);
            hashval = 31*hashval + hash<string>()(p.gender);
            hashval = 31*hashval + hash<string>()(p.birthday);
            return hashval;
        }
    };
}