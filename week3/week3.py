class User:
    def __init__(self):
        self._friends = []
        self._votes = {}

    def add_friend(self, f):
        self._friends.append(f)

    def get_friends(self):
        return self._friends

    def add_vote(self, p, v):
        self._votes[p] = v

    def get_votes(self):
        return self._votes

    def find_notifications(self, posts, t):
        notifications = []
        for p in posts:
            net = 0

            for f in self.get_friends():
                if p in f.get_votes():
                    net += f.get_votes()[p]

            if net >= t:
                notifications += [p]

        return notifications

if __name__ == "__main__":
    n = int(input())
    users = {}
    for i in range(n):
        u1, u2 = (int(x) - 1 for x in input().split())

        if u1 not in users: users[u1] = User()
        if u2 not in users: users[u2] = User()

        users[u1].add_friend(users[u2])
        users[u2].add_friend(users[u1])

    m = int(input())
    posts = {}
    for i in range(m):
        u, p, v = (int(x) for x in input().split())
        posts[p] = True
        users[u - 1].add_vote(p, v)

    u, t = (int(x) for x in input().split())
    [print(p) for p in users[u - 1].find_notifications(posts, t)]
