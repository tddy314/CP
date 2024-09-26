class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        double totalCost = numeric_limits<double>::max();
        double currentTotalQuality = 0;
        // Store wage-to-quality ratio along with quality
        vector<pair<double, int>> wageToQualityRatio;

        // Calculate wage-to-quality ratio for each worker
        for (int i = 0; i < n; i++) {
            wageToQualityRatio.push_back(
                {static_cast<double>(wage[i]) / quality[i], quality[i]});
        }

        // Sort workers based on their wage-to-quality ratio
        sort(wageToQualityRatio.begin(), wageToQualityRatio.end());

        // Use a priority queue to keep track of the highest quality workers
        priority_queue<int> workers;

        // Iterate through workers
        for (int i = 0; i < n; i++) {
            workers.push(wageToQualityRatio[i].second);
            currentTotalQuality += wageToQualityRatio[i].second;

            // If we have more than k workers,
            // remove the one with the highest quality
            if (workers.size() > k) {
                currentTotalQuality -= workers.top();
                workers.pop();
            }

            // If we have exactly k workers,
            // calculate the total cost and update if it's the minimum
            if (workers.size() == k) {
                totalCost = min(totalCost, currentTotalQuality *
                                               wageToQualityRatio[i].first);
            }
        }
        return totalCost;
    }
};


// sort the workers follow the increament of the ratio between wage and quality
// use priority - queue to control the quality of the worker join the group
// eliminate the one that has the highest quality when adding new worker to the group and the group is full
// whenever the group reach its maxium size, you can calculate the total cost for the current group by multiplying the value of current total quality with the ratio of the last worker
// Because the last worker that joined the group has the biggest ratio
// The cost can be calculated as follow: totalCost = min{totalQuality * ratioOftheIthWorkerOftheGroup} 
