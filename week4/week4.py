#!/bin/python
"""UWindsor CS POTW - Week 4, The Blackboard API.

Author: Adam Vandolder (github.com/avandolder)
"""


class Course(object):
    """Holds the parent and child course sets."""

    def __init__(self):
        """Initialize the parent and child sets."""
        self.parents = set()
        self.children = set()


def can_graduate(courses, required):
    """Determine if it is possible to graduate."""
    # satisfied holds all courses with satisfied prerequisites.
    satisfied = list(filter(lambda x: not courses[x].parents, courses))
    can_take = 0

    while satisfied:
        c = satisfied.pop()
        can_take += 1

        if can_take >= required:
            return True

        for child in courses[c].children:
            courses[child].parents.remove(c)

            if not courses[child].parents:
                satisfied.append(child)

    return False


if __name__ == "__main__":
    courses = {}
    required = int(input())
    for i in range(int(input())):
        a, b = map(int, input().split())

        if a not in courses:
            courses[a] = Course()
        if b not in courses:
            courses[b] = Course()

        courses[a].children.add(b)
        courses[b].parents.add(a)

    print("Good" if can_graduate(courses, required) else "Bad")
