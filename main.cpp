#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

enum WEEKDAY {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

string printWEEKDAY(WEEKDAY weekday) {
    switch (weekday) {
        case WEEKDAY::MONDAY: return "MONDAY";
        case WEEKDAY::TUESDAY: return "TUESDAY";
        case WEEKDAY::WEDNESDAY: return "WEDNESDAY";
        case WEEKDAY::THURSDAY: return "THURSDAY";
        case WEEKDAY::FRIDAY: return "FRIDAY";
        case WEEKDAY::SATURDAY: return "SATURDAY";
        case WEEKDAY::SUNDAY: return "SUNDAY";
    }
}


class Rating {
public:
    string subject;
    vector<unsigned int> GradeList;
    unsigned int SemesterGrade;

    explicit Rating(string subject) : subject(std::move(subject)) {
        SemesterGrade = 0;
        vector<unsigned int> ocen;
        GradeList = ocen;
    }

    virtual ~Rating() = default;
};

class Man {
private:
    string Name;
    unsigned int Age;
public:
    Man() {}

    Man(string name, unsigned int age) : Name(std::move(name)), Age(age) {}

    virtual ~Man() = default;

    const string &getName() const {
        return Name;
    }
};

class Pupil : public Man {
private:
    vector<Rating> RatingList;
public:
    Pupil(const string &name, unsigned int age, vector<Rating> ratingList) :
            Man(name, age), RatingList(std::move(ratingList)) {}

    const vector<Rating> &getRatingList() const {
        return RatingList;
    }

    ~Pupil() override = default;

    void setRatingList(const vector<Rating> &ratingList) {
        RatingList = ratingList;
    }

    void print_grades() {
        cout << "   " << getName() << " Subjects: " << endl;
        for (unsigned int i = 0; i < RatingList.size(); i++) {
            cout << "     " << RatingList[i].subject << ": ";
            for (unsigned int j = 0; j < RatingList[i].GradeList.size(); j++) {
                cout << RatingList[i].GradeList[j] << " ";
            }
            cout << endl << "     Semester grade: " << RatingList[i].SemesterGrade << endl;
        }
    };
};

class Teacher : public Man {
private:
    vector<string> SubjectList;
    unsigned int Classroom;
public:
    Teacher() {}

    Teacher(const string &name, unsigned int age, vector<string> subjectList, unsigned int classroom) :
            Man(name, age), SubjectList(std::move(subjectList)), Classroom(classroom) {}

    ~Teacher() override = default;

    const vector<string> &getSubjectList() const {
        return SubjectList;
    }

    unsigned int getClassroom() const {
        return Classroom;
    }

    Pupil addGrade(Pupil pupil, unsigned int grade, const string& teacher_subject) {
        if (grade <= 5) {
            bool found = false;
            unsigned int i = 0;
            while ((i < SubjectList.size()) && (not found)) {
                if (SubjectList[i] == teacher_subject) {
                    found = true;
                }
                else {
                    i++;
                }
            }
            if (found) {
                found = false;
                i = 0;
                vector<Rating> get_RatingList = pupil.getRatingList();
                while ((i < get_RatingList.size()) && (not found)) {
                    if (get_RatingList[i].subject == teacher_subject) {
                        found = true;
                    }
                    else {
                        i++;
                    }
                }
                if (found) {
                    get_RatingList[i].GradeList.push_back(grade);
                    pupil.setRatingList(get_RatingList);
                    return pupil;
                }
            }
        }
    }

    Pupil setSemesterGrade(Pupil pupil, string teacher_subject) {
        bool found = false;
        unsigned int i = 0;
        while ((i < SubjectList.size()) && (not found)) {
            if (SubjectList[i] == teacher_subject) {
                found = true;
            }
            else {
                i++;
            }
        }
        if (found) {
            found = false;
            i = 0;
            vector<Rating> get_RatingList = pupil.getRatingList();
            while ((i < get_RatingList.size()) && (not found)) {
                if (get_RatingList[i].subject == teacher_subject) {
                    found = true;
                }
                else {
                    i++;
                }
            }
            if (found) {
                unsigned int j = 0;
                unsigned int grade = 0;
                while (j < get_RatingList[i].GradeList.size()) {
                    grade += get_RatingList[i].GradeList[j];
                    j++;
                }
                grade = round(grade / j);
                get_RatingList[i].SemesterGrade = grade;
                pupil.setRatingList(get_RatingList);
                return pupil;
            }
        }
    }
};

class SchoolClass {
private:
    string Name;
    vector<Pupil> PupilList;
public:
    SchoolClass() {}

    SchoolClass(string name, vector<Pupil> pupilList) : Name(std::move(name)), PupilList(std::move(pupilList)) {}

    virtual ~SchoolClass() = default;

    const string &getName() const {
        return Name;
    }

    void addPupil(Pupil pupil) {
        PupilList.push_back(pupil);
    }

    void printschoolboyGrades() {
        cout << " GRADES OF CLASS " << Name << ": " << endl;
        for (auto & it : PupilList) {
            it.print_grades();
        }
        cout << endl;
    }
};

class Lesson {
private:
    SchoolClass schoolclass;
    Teacher teacher;
    string subject;
    WEEKDAY weekday;
    time_t TimeStart;
    time_t TimeEnd;
public:
    Lesson(const SchoolClass &schoolclass, const Teacher &teacher, const string &subject, WEEKDAY weekday,
           time_t timeStart, time_t timeEnd) : schoolclass(schoolclass), teacher(teacher), subject(subject),
                                               weekday(weekday), TimeStart(timeStart), TimeEnd(timeEnd) {}

    virtual ~Lesson() = default;

    const SchoolClass &getSchoolclass() const {
        return schoolclass;
    }

    const Teacher &getTeacher() const {
        return teacher;
    }

    void printLesson() {
        cout << printWEEKDAY(weekday) << endl;
        cout << schoolclass.getName() << " Lesson of " << subject << " from " << TimeStart << " to " << TimeEnd << endl;
    };
};

class Lesson_builder {
private:
    SchoolClass schoolclass;
    Teacher teacher;
    string subject;
    WEEKDAY weekday;
    time_t TimeStart;
    time_t TimeEnd;
public:
    Lesson_builder() {}

    virtual ~Lesson_builder() = default;

    Lesson build() {
        return Lesson{
                schoolclass,
                teacher,
                subject,
                weekday,
                TimeStart,
                TimeEnd
        };
    }

    void setSchoolclass(const SchoolClass &schoolclass) {
        Lesson_builder::schoolclass = schoolclass;
    }

    void setTeacher(const Teacher &teacher) {
        Lesson_builder::teacher = teacher;
    }

    void setSubject(const string &subject) {
        bool found = false;
        unsigned int i = 0;
        while ((i < teacher.getSubjectList().size()) && (not found)) {
            if (teacher.getSubjectList()[i] == subject) {
                found = true;
            }
            else {
                i++;
            }
        }
        if (found) {
            Lesson_builder::subject = subject;
        }
    }

    void setWeekday(WEEKDAY weekday) {
        Lesson_builder::weekday = weekday;
    }

    void setTimeStart(const time_t &timeStart) {
        Lesson_builder::TimeStart = timeStart;
    }

    void setTimeEnd(const time_t &timeEnd) {
        Lesson_builder::TimeEnd = timeEnd;
    }
};

class Schedule {
private:
    vector<Lesson> LessonList;
public:
    explicit Schedule(vector<Lesson> lessonList) : LessonList(std::move(lessonList)) {}

    virtual ~Schedule() = default;

    void addLesson(const Lesson& lesson) {
        LessonList.push_back(lesson);
    }

    void printSchedule(SchoolClass schoolclass) {  ///////////// похорошему нужно отсортировать каждый раз перед выводом по 1) дню недели 2) классу 3) времени
        cout << "Schedule of class " << schoolclass.getName() << endl;
        cout << "---------------------------------------" << endl;
        for (unsigned int i = 0; i < LessonList.size(); i++) {
            if (LessonList[i].getSchoolclass().getName() == schoolclass.getName()) {
                LessonList[i].printLesson();
            }
        }
        cout << "---------------------------------------" << endl;
        cout << endl;
    }
    void printSchedule(Teacher teacher) {  ///////////// похорошему нужно отсортировать каждый раз перед выводом по 1) дню недели 2) учителю 3) времени
        cout << "Schedule of teacher " << teacher.getName() << endl;
        cout << "---------------------------------------" << endl;
        for (unsigned int i = 0; i < LessonList.size(); i++) {
            if ((LessonList[i].getTeacher().getClassroom() == teacher.getClassroom()) &&
                (LessonList[i].getTeacher().getName() == teacher.getName())) {
                LessonList[i].printLesson();
            }
        }
        cout << "---------------------------------------" << endl;
        cout << endl;
    }
};

class School {
private:
    string Name;
    vector<SchoolClass> SchoolClassList;
    vector<Teacher> TeacherList;
    Schedule schedule;
public:
    School(string name, vector<SchoolClass> schoolClassList, vector<Teacher> teacherList, const Schedule &schedule) :
            Name(std::move(name)), SchoolClassList(std::move(schoolClassList)), TeacherList(std::move(teacherList)), schedule(schedule) {}

    virtual ~School() = default;

    const Schedule &getSchedule() const {
        return schedule;
    }

    void addSchoolClass(const SchoolClass& schoolclass) {
        SchoolClassList.push_back(schoolclass);
    }

    void addTeacher(const Teacher& teacher) {
        TeacherList.push_back(teacher);
    }

    void printGradesByClass() {
        cout << "GRADES OF ALL SCHOOL " << Name << ": " << endl;
        for (auto & it : SchoolClassList) {
            it.printschoolboyGrades();
        }
    }
};

int main() {

    //предметы и оценки учеников
    Rating r1("Biology");
    Rating r2("Chemistry");
    Rating r3("Physics");
    Rating r4("OBJ");
    vector<Rating> grades;
    grades.push_back(r1);
    grades.push_back(r2);
    grades.push_back(r3);
    grades.push_back(r4);

    //ученики
    Pupil uch1("Настя", 12, grades);
    Pupil uch2("Алексей", 17, grades);

    //предметы учителей
    vector<string> predmeti1;
    predmeti1.emplace_back("Biology");
    predmeti1.emplace_back("Chemistry");
    vector<string> predmeti2;
    predmeti2.emplace_back("Physics");
    predmeti2.emplace_back("OBJ");

    //учителя
    Teacher uchit1("Вова", 20, predmeti1, 202);
    Teacher uchit2("Лера", 100, predmeti2, 304);


    //ставим оценки
    uch1 = uchit1.addGrade(uch1, 5, "Biology");
    uch1 = uchit1.addGrade(uch1, 4, "Biology");
    uch1 = uchit1.addGrade(uch1, 5, "Biology");
    uch1 = uchit1.addGrade(uch1, 3, "Chemistry");
    uch1 = uchit1.addGrade(uch1, 3, "Chemistry");
    uch1 = uchit1.addGrade(uch1, 2, "Chemistry");

    uch1 = uchit1.setSemesterGrade(uch1, "Biology");
    uch1 = uchit1.setSemesterGrade(uch1, "Chemistry");
    uch1 = uchit2.addGrade(uch1, 5, "Physics");
    uch1 = uchit2.addGrade(uch1, 4, "Physics");
    uch1 = uchit2.addGrade(uch1, 3, "OBJ");
    uch1 = uchit2.setSemesterGrade(uch1, "Physics");
    uch1 = uchit2.setSemesterGrade(uch1, "OBJ");

    uch1.print_grades();
    cout << endl;

    uch2 = uchit1.addGrade(uch2, 2, "Biology");
    uch2 = uchit1.addGrade(uch2, 3, "Biology");
    uch2 = uchit1.addGrade(uch2, 1, "Biology");
    uch2 = uchit1.addGrade(uch2, 5, "Chemistry");
    uch2 = uchit1.addGrade(uch2, 5, "Chemistry");
    uch2 = uchit1.setSemesterGrade(uch2, "Biology");
    uch2 = uchit1.setSemesterGrade(uch2, "Chemistry");
    uch2 = uchit2.addGrade(uch2, 4, "Physics");
    uch2 = uchit2.addGrade(uch2, 4, "Physics");
    uch2 = uchit2.addGrade(uch2, 3, "OBJ");
    uch2 = uchit2.addGrade(uch2, 5, "OBJ");
    uch2 = uchit2.setSemesterGrade(uch2, "Physics");
    uch2 = uchit2.setSemesterGrade(uch2, "OBJ");

    //класс
    vector<Pupil> ucheniki;
    ucheniki.emplace_back(uch1);
    ucheniki.emplace_back(uch2);
    SchoolClass A11("A11", ucheniki);

    //урок1
    Lesson_builder builder;
    builder.setSchoolclass(A11);
    builder.setSubject("Biology");
    builder.setTeacher(uchit1);
    builder.setTimeStart(1010);
    builder.setTimeEnd(1140);
    builder.setWeekday(MONDAY);
    Lesson urok1 = builder.build();

    //урок2
    builder.setSchoolclass(A11);
    builder.setSubject("Physics");
    builder.setTeacher(uchit2);
    builder.setTimeStart(830);
    builder.setTimeEnd(1000);
    builder.setWeekday(MONDAY);
    Lesson urok2 = builder.build();

    //расписание
    vector<Lesson> uroki;
    uroki.emplace_back(urok1);
    uroki.emplace_back(urok2);
    Schedule raspis(uroki);

    //школа
    vector<SchoolClass> klassi;
    klassi.emplace_back(A11);
    vector<Teacher> uchitelya;
    uchitelya.emplace_back(uchit1);
    uchitelya.emplace_back(uchit2);
    School shkola("MOANC", klassi, uchitelya, raspis);
    //............................................................................

    shkola.printGradesByClass(); // вывод всех оценок школы
    Schedule sch = shkola.getSchedule();
    sch.printSchedule(A11); // вывод рассписания класса
    sch.printSchedule(uchit1); // вывод рассписания учителя


    return 0;
}
