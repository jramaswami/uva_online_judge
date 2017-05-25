// UVA :: 10141 :: Request for Proposal
// https://uva.onlinejudge.org/external/101/10141.pdf

#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int requirements_count, proposals_count;
    cin >> requirements_count >> proposals_count;
    int rfp = 1;
    while (requirements_count || proposals_count) {
        cin.ignore(255, '\n');
        for (auto r = 0; r < requirements_count; ++r) {
            string requirement;
            getline(cin, requirement);
        }
        string best_proposal = "";
        double best_score = 0.00;
        double least_cost = numeric_limits<double>::max();
        for (auto p = 0; p < proposals_count; ++p) {
            string proposal_name;
            getline(cin, proposal_name);
            double proposal_cost;
            cin >> proposal_cost;
            int requirements_met;
            cin >> requirements_met;
            cin.ignore(255, '\n');
            for (auto r = 0; r < requirements_met; ++r) {
                string met_requirement;
                getline(cin, met_requirement);
            }
            double proposal_score = 1.00;
            if (requirements_met < requirements_count) {
                proposal_score = static_cast<double>(requirements_met) / static_cast<double>(requirements_count);
            }
            if (proposal_score > best_score) {
                best_proposal = proposal_name;
                best_score = proposal_score;
                least_cost = proposal_cost;
            }
            if (proposal_score == best_score && proposal_cost < least_cost) {
                best_proposal = proposal_name;
                least_cost = proposal_cost;
            }
        }

        cout << "RFP #" << rfp << "\n" << best_proposal << "\n";

        ++rfp;
        cin >> requirements_count >> proposals_count;
        if (requirements_count && proposals_count) {
            cout << "\n";
        } else {
            break;
        }
    }

    return 0;
}
