#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class User
{
    std::vector<std::shared_ptr<User>> friends;
    std::vector<int> notifications;
    std::unordered_map<int, int> votes;

public:
    void add_friend(auto f) { friends.push_back(f); }
    auto& get_friends() { return friends; }
    void add_vote(int p, int v) { votes[p] = v; }
    auto& get_votes() { return votes; }
    std::vector<int>& find_notifications(auto posts, int t);
};

std::vector<int>& User::find_notifications(auto posts, int t)
{
    for (auto p : posts)
    {
        int net = 0;

        for (auto f : get_friends())
        {
            auto& votes = f->get_votes();

            if (votes.find(p) != votes.end())
                net += votes[p];
        }

        if (net >= t)
            notifications.push_back(p);
    }

    return notifications;
}

auto get_users(int n)
{
    std::unordered_map<int, std::shared_ptr<User>> users;

    for (int i = 0; i < n; i++)
    {
        int a, b;
        std::cin >> a >> b;

        // If either of the users have not been encountered before, create them.
        if (users.find(a) == users.end())
            users[a] = std::make_shared<User>();
        if (users.find(b) == users.end())
            users[b] = std::make_shared<User>();

        users[a]->add_friend(users[b]);
        users[b]->add_friend(users[a]);
    }

    return users;
}

auto get_posts(auto& users, int n)
{
    std::unordered_set<int> posts;

    for (int i = 0; i < n; i++)
    {
        int u, p, v;
        std::cin >> u >> p >> v;

        posts.insert(p);

        if (users.find(u) == users.end())
            users[u] = std::make_shared<User>();

        users[u]->add_vote(p, v);
    }

    return posts;
}

int main(int argc, char *argv[])
{
    int n;

    // Get the friend relationships of the users.
    std::cin >> n;
    auto users = get_users(n);

    // Get the votes on the various posts.
    std::cin >> n;
    auto posts = get_posts(users, n);

    int u, t;
    std::cin >> u >> t;
    // Find the notifications for user u that pass the threshold t.
    for (auto p : users[u]->find_notifications(posts, t))
        std::cout << p << std::endl;

    return 0;
}
