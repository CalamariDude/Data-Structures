#include <iostream>
#include <stack>
using namespace std;

int main() {

        for(int a =0; a != 0; cin >> a) {
                int n;
                cin >> n;
                int truckscoming[3000];
                for(int i = 0; i < n; i++) {
                        int number;
                        cin >> number;
                        truckscoming[i]=number;
                }
                stack<int> truckswaiting;
                stack<int> truckspassed;
                bool doneflag = false;
                for(int start = 0, onnumber = 0; truckspassed.size() < n, !doneflag;) {
                        if (truckscoming[start] == onnumber+1) {
                                truckspassed.push(truckscoming[start]);
                                onnumber++;
                                start++;
                        }
                        else if((!truckswaiting.empty()) && truckswaiting.top() == onnumber+1) {
                                truckspassed.push(truckswaiting.top());
                                truckswaiting.pop();
                                onnumber++;
                        }
                        else if(truckscoming[start] < truckswaiting.top()) {
                                truckswaiting.push(truckscoming[start]);
                                start++;
                        }
                        else{
                                doneflag=true;
                                cout<< "no" << endl;
                        }
                }
                if(!doneflag) {
                        cout<< "yes" << endl;
                }

                a = 5;
        }

        return 0;
}
