/*
 * 1357. Apply Discount Every n Orders
 * 
 * There is a sale in a supermarket, there will be a discount every n customer.
 * There are some products in the supermarket where the id of the i-th product is products[i] and the price per unit of this product is prices[i].
 * The system will count the number of customers and when the n-th customer arrive he/she will have a discount on the bill. (i.e if the cost is x the new cost is x - (discount * x) / 100). Then the system will start counting customers again.
 * The customer orders a certain amount of each product where product[i] is the id of the i-th product the customer ordered and amount[i] is the number of units the customer ordered of that product.
 * 
 * Implement the Cashier class:
 * Cashier(int n, int discount, int[] products, int[] prices) Initializes the object with n, the discount, the products and their prices.
 * double getBill(int[] product, int[] amount) returns the value of the bill and apply the discount if needed. Answers within 10^-5 of the actual value will be accepted as correct.
 * 
 * Example 1:
 * Input
 * ["Cashier","getBill","getBill","getBill","getBill","getBill","getBill","getBill"]
 * [[3,50,[1,2,3,4,5,6,7],[100,200,300,400,300,200,100]],[[1,2],[1,2]],[[3,7],[10,10]],[[1,2,3,4,5,6,7],[1,1,1,1,1,1,1]],[[4],[10]],[[7,3],[10,10]],[[7,5,3,1,6,4,2],[10,10,10,9,9,9,7]],[[2,3,5],[5,3,2]]]
 * Output
 * [null,500.0,4000.0,800.0,4000.0,4000.0,7350.0,2500.0]
 * Explantion:
 * Cashier cashier = new Cashier(3,50,[1,2,3,4,5,6,7],[100,200,300,400,300,200,100]);
 * cashier.getBill([1,2],[1,2]);                        // return 500.0, bill = 100 + 200 = 300, no discount
 * cashier.getBill([3,7],[10,10]);                      // return 4000.0, bill = 3000 + 700 = 3700, no discount
 * 
 * Example 2:
 * Input
 * ["Cashier","getBill","getBill","getBill","getBill","getBill","getBill"]
 * [[3,50,[1,2,3,4,5,6,7],[100,200,300,400,300,200,100]],[[1,2],[1,2]],[[3,7],[10,10]],[[1,2,3,4,5,6,7],[1,1,1,1,1,1,1]],[[4],[10]],[[7,3],[10,10]],[[7,5,3,1,6,4,2],[10,10,10,9,9,9,7]]]
 * Output
 * [null,500.0,4000.0,800.0,4000.0,4000.0,7350.0]
 * Explantion:
 * Cashier cashier = new Cashier(3,50,[1,2,3,4,5,6,7],[100,200,300,400,300,200,100]);
 * cashier.getBill([1,2],[1,2]);                        // return 500.0, bill = 100 + 200 = 300, no discount
 * cashier.getBill([3,7],[10,10]);                      // return 4000.0, bill = 3000 + 700 = 3700, no discount
 * cashier.getBill([1,2,3,4,5,6,7],[1,1,1,1,1,1,1]);  // return 800.0, bill = 100 + 200 + 300 + 400 + 300 + 200 + 100 = 3700, discount = 500
 * cashier.getBill([4],[10]);                          // return 4000.0, bill = 400 * 10 = 4000, no discount
 * cashier.getBill([7,3],[10,10]);                     // return 4000.0, bill = 700 + 300 = 1000, no discount   
 * 
 * Note:
 * 1 <= n <= 10^4
 * 0 <= discount <= 100
 * 1 <= products.length <= 200
 * products[i] is in the range [1, 2000]
 * prices[i] is in the range [1, 10^4]
 * 1 <= products.length <= prices.length
 * The products given are guaranteed to be unique.
 * 1 <= product.length <= products.length
 * 1 <= amount.length <= products.length
 * product[i] exists in products.
 * amount[i] is positive.
 * At most 1000 calls will be made to getBill.
 * Answers within 10^-5 of the actual value will be accepted as correct.
 * 
 */
#include <vector>
#include <unordered_map>

using namespace std;

class Cashier {
private:
    int n;
    int discount;
    unordered_map<int, int> priceMap;
    int customerCount;

public:
    Cashier(int n, int discount, vector<int>& products, vector<int>& prices) {
        this->n = n;
        this->discount = discount;
        this->customerCount = 0;
        for (int i = 0; i < products.size(); ++i) {
            priceMap[products[i]] = prices[i];
        }
    }
    
    double getBill(vector<int> product, vector<int> amount) {
        customerCount++;
        double total = 0.0;
        for (int i = 0; i < product.size(); ++i) {
            total += priceMap[product[i]] * amount[i];
        }
        if (customerCount % n == 0) {
            total = total * (100 - discount) / 100;
        }
        return total;
    }
};

/**
 * Your Cashier object will be instantiated and called as such:
 * Cashier* obj = new Cashier(n, discount, products, prices);
 * double param_1 = obj->getBill(product,amount);
 */