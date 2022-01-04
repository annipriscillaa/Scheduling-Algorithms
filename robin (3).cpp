#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid;
    int s_time;
    int c_time;
    int t_time;
    int w_time;
    int b_time;
    int a_time;
    int r_time;
};
static bool compare(process a, process b)
{
    return a.a_time < b.a_time;
}
static bool compare2(process a, process b)
{
    return a.pid < b.pid;
}
int main()
{
    int n, tq, count = 0, curr = 0;
    float avg_tt = 0, avg_wt = 0, total_tt = 0, total_wt = 0;
    cout << "\n Enter No of Process";
    cin >> n;
    cout << "\n Enter Time Quanta";
    cin >> tq;
    process p[n];
    vector<int> burst_time(n+1, 0);
    for (int i = 0; i < n; i++)
    {
        cout << "\nProcess " << i + 1 << "\n";
        cout << "\nArrival Time: ";
        cin >> p[i].a_time;
        cout << "\nBurst Time: ";
        cin >> p[i].b_time;
        p[i].pid = i + 1;
        burst_time[p[i].pid] = p[i].b_time;
        
    }
    sort(p, p + n, compare);
    queue<int> q;
    vector<int> mark(n, false);
    q.push(0);
    mark[0] = true;

    while (count != n)
    {
        int ind = q.front();
        q.pop();
        if (burst_time[p[ind].pid] == p[ind].b_time)
        {
            p[ind].s_time = max(curr,p[ind].a_time);
            curr=p[ind].s_time;
            //p[ind].s_time = curr;
        }
        if (burst_time[p[ind].pid] - tq > 0)
        {
            curr += tq;
            burst_time[p[ind].pid] -= tq;
        }
        else
        {
            curr += burst_time[p[ind].pid];
            burst_time[p[ind].pid] = 0;
            count++;

            p[ind].c_time = curr;
            p[ind].t_time = p[ind].c_time - p[ind].a_time;
            p[ind].w_time = p[ind].t_time - p[ind].b_time;
            p[ind].r_time = p[ind].s_time + p[ind].a_time;

            total_wt += p[ind].w_time;
            total_tt += p[ind].t_time;
        }
        for (int i = 1; i < n; i++)
        {
            int id=p[i].pid;
            if (p[i].a_time <= curr && !mark[i] && burst_time[id] > 0)
            {
                mark[i] = true;
                q.push(i);
            }
        }
        if (burst_time[p[ind].pid] > 0)
        {
            q.push(ind);
        }
        if (q.empty())
        {
            for (int i = 1; i < n; i++)
            {
                int id=p[i].pid;
                if (burst_time[id] > 0)
                {
                    mark[i] = true;
                    q.push(i);
                }
            }
        }

    }

    avg_wt = (total_wt / n);
    avg_tt = (total_tt / n);
    sort(p, p + n, compare2);
    cout << "\nPID\t\tAT\t\tBT\t\tST\t\tCT\t\tTAT\t\tWT";
    for (int i = 0; i < n; i++)
    {
        cout << "\n"
             << p[i].pid << "\t\t" << p[i].a_time << "\t\t" << p[i].b_time << "\t\t" << p[i].s_time << "\t\t" << p[i].c_time << "\t\t" << p[i].t_time << "\t\t" << p[i].w_time;
    }
    cout << "\nAverage Waiting Time :" << avg_wt;
    cout << "\nAverage TurnAround Time :" << avg_tt;
    return 0;
}