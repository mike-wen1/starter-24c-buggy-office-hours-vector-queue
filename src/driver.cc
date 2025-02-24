#include <iostream>

#include "functions.hpp"
#include "office-hours-queue.hpp"
#include "staff.hpp"
#include "student.hpp"

using namespace std;

int main() {
  OfficeHoursQueue queue;

  // Adding students
  Student s1 = {"Alice", 1, 90.0};
  AddStudent(queue, s1);

  Student s2 = {"Bob", 2, 85.0};
  AddStudent(queue, s2);

  Student s3 = {"Charlie", 3, 95.0};
  AddStudent(queue, s3);

  // Adding staff members
  Staff st1 = {"TA Colt", 101};
  AddStaff(queue, st1);

  Staff st2 = {"TA Abilene", 102};
  AddStaff(queue, st2);

  HelpNextStudent(queue);
  HelpNextStudent(queue);
  HelpNextStudent(queue);
}