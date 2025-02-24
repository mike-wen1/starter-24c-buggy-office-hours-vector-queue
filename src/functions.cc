#include "functions.hpp"

#include <iostream>
#include <random>

using namespace std;

constexpr int kRandomMin = 5;
constexpr int kRandomMax = 20;

void AddStudent(OfficeHoursQueue& queue, const Student& student) {
  // Update arrival order
  int new_student_arrival_order = queue.student_arrival_counter + 1;

  // Go through and sort by attendence, then arrival order
  bool at_end = true;
  for (int i = 0; i < (int)queue.student_queue.size(); i++) {
    if (student.attendance_percentage >
        queue.student_queue[i]
            .attendance_percentage) {  // Should account for arrival order
      queue.student_queue.push_back(
          queue.student_queue[(int)queue.student_queue.size() - 1]);
      for (int j = (int)queue.student_queue.size() - 1; j > i; j--) {
        queue.student_queue[j] = queue.student_queue[j - 1];
      }
      queue.student_queue[i] = Student{student.name,
                                       student.student_id,
                                       student.attendance_percentage,
                                       new_student_arrival_order};

      at_end = false;
      break;
    }
  }

  if (at_end) {
    queue.student_queue.push_back(Student{student.name,
                                          student.student_id,
                                          student.attendance_percentage,
                                          new_student_arrival_order});
  }

  queue.student_arrival_counter += 1;
}

void AddStaff(OfficeHoursQueue& queue, const Staff& staff) {
  /*
  queue.staff_queue.push_back(staff);
  queue.staff_queue.back().arrival_order = queue.staff_arrival_counter;
  queue.staff_arrival_counter += 1;

  unsigned int index = queue.staff_queue.size() - 1;
  while (index > 0) {
    const Staff& current = queue.staff_queue[index];
    const Staff& previous = queue.staff_queue[index - 1];

    if (current.encounter_count > previous.encounter_count) {
      Staff temp = queue.staff_queue[index - 1];
      queue.staff_queue[index - 1] = queue.staff_queue[index];
      queue.staff_queue[index] = temp;
      index--;
    } else if (current.encounter_count == previous.encounter_count) {
      if (current.arrival_order > previous.arrival_order) {
        Staff temp = queue.staff_queue[index - 1];
        queue.staff_queue[index - 1] = queue.staff_queue[index];
        queue.staff_queue[index] = temp;
        index--;
      } else {
        break;
      }
    } else {
      break;
    }
  }
  */

  // Update arrival order
  int new_staff_arrival_order = queue.staff_arrival_counter + 1;

  // Go through, sort by fewer "encounters" (students helped), then by less
  // total help time, then arrival order Again, looping from the start to the
  // end of the queue should sort by arrival order
  bool at_end = true;
  for (int i = 0; i < (int)queue.staff_queue.size(); i++) {
    if ((staff.encounter_count < queue.staff_queue[i].encounter_count) ||
        (staff.encounter_count == queue.staff_queue[i].encounter_count &&
         staff.total_help_time < queue.staff_queue[i].total_help_time)) {
      queue.staff_queue.push_back(
          queue.staff_queue[(int)queue.staff_queue.size() - 1]);
      for (int j = (int)queue.staff_queue.size() - 1; j > i; j--) {
        queue.staff_queue[j] = queue.staff_queue[j - 1];
      }
      queue.staff_queue[i] = Staff{staff.name,
                                   staff.staff_id,
                                   staff.encounter_count,
                                   new_staff_arrival_order,
                                   staff.total_help_time};

      at_end = false;
      break;
    }
  }
  if (at_end) {
    queue.staff_queue.push_back(Staff{staff.name,
                                      staff.staff_id,
                                      staff.encounter_count,
                                      new_staff_arrival_order,
                                      staff.total_help_time});
  }

  queue.staff_arrival_counter += 1;
}

void HelpNextStudent(OfficeHoursQueue& queue) {
  if (queue.student_queue.empty()) {
    std::cout << "No students in queue.\n";
    return;
  }
  if (queue.staff_queue.empty()) {
    std::cout << "No staff available.\n";
    return;
  }

  Student student = queue.student_queue[0];
  queue.student_queue.erase(queue.student_queue.begin());
  Staff staff = queue.staff_queue[0];
  queue.staff_queue.erase(queue.staff_queue.begin());

  // Generate random help time between kRandomMin and kRandomMax minutes
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(kRandomMin, kRandomMax);
  int help_time = dist(gen);

  staff.encounter_count++;
  staff.total_help_time += help_time;
  AddStaff(queue, staff);

  std::cout << "Staff " << staff.name << " helped student " << student.name
            << " for " << help_time << " minutes.\n";
}

bool IsStudentQueueEmpty(const OfficeHoursQueue& queue) {
  return queue.student_queue.empty();
}

bool IsStaffQueueEmpty(const OfficeHoursQueue& queue) {
  return queue.staff_queue.empty();
}