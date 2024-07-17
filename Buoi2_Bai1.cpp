#include <iostream>
#include <time.h>
#define MAX 50
#include <cstdlib>
using namespace std;
//Bai 1_a
//---------------------------------------------------------------------------
void TaoMangMotChieuLonHonBang15(){
	int a[MAX];
	for(int i=15;i<MAX;i++){
		a[i]= rand() % (MAX+1);		
	}
}
void XuatMang1a(){
	int a[MAX];
	cout << "Mang duoc tao:"<< endl;
	for(int i=15;i<MAX;i++){
			cout << "Phan tu thu " << i << ":" << a[i] << endl;
	}	
}
//----------------------------------------------------------------------------
//Bai 1_b
//----------------------------------------------------------------------------
void TaoMangToanSoChan(){
	int b[MAX];
	int so;
	for(int i = 1;i<=MAX;i++){
		so = rand() % (MAX+1);
		if(so % 2 == 0 && so != 0){
			b[i] = so;
		}
	}
}
void XuatMang1b(){
	int b[MAX];
	cout << "Mang duoc tao:"<< endl;
	for(int i=1;i<=MAX;i++){
			cout << "Phan tu thu " << i << ":" << b[i] << endl;
	}	
}
//----------------------------------------------------------------------------
//Cau 1_c
int LinearSearch(int a[], int x) {
    for (int i = 0; i < MAX; ++i) {
        if (a[i] == x) {
            return i;
        }
    }
    return -1;
}
//-----------------------------------------------------------------------------
//Cau 1_d
void InterchangeSort(int a[], bool giatang = true) {
    for (int i = 0; i < MAX - 1; ++i) {
        for (int j = i + 1; j < MAX; ++j) {
            if ((giatang && a[i] > a[j]) || (!giatang && a[i] < a[j])) {
                swap(a[i], a[j]);
            }
        }
    }
}
//-----------------------------------------------------------------------------
//Cau 1_e
int BinarySearch(int a[], int x) {
    int left = 0, right = MAX - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == x) {
            return mid;
        }
        if (a[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
//------------------------------------------------------------------------------
// Cau 1_f
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
void SelectionSort(int a[]) {
    for (int i = 0; i < MAX - 1; ++i) {
        int sonhonhat = i;
        for (int j = i + 1; j < MAX; ++j) {
            if (a[j] < a[sonhonhat]) {
                sonhonhat = j;
            }
        }
        swap(a[i], a[sonhonhat]);
    }
}
//Cau 1_g
int partition(int a[], int low, int high) {
    int pivot = a[high]; // 
    int i = low - 1; // 

    for (int j = low; j < high; ++j) {
        if (a[j] < pivot) {
            ++i;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1; 
}

void QuickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high); 

        QuickSort(a, low, pi - 1); 
        QuickSort(a, pi + 1, high); 
    }
}
//----------------------------------------------------------------------------
int main(){
	srand(time(0));
	int a[MAX];
	cout << "Cau 1a:"<<endl;
	TaoMangMotChieuLonHonBang15();
	XuatMang1a();
	cout << "Cau 1b"<<endl;
	TaoMangToanSoChan();
	XuatMang1b();
	int x,n;
	cout <<"Nhap gia tri can tim:";
	cin >> x;
	int index = LinearSearch(a, x);
    if (index != -1) {
        cout << "Tim thay " << x << " tai vi tri " << index << " bang Linear Search" << endl;
    } else {
        cout << x << " khong tim thay bang Linear Search" << endl;
    }
    InterchangeSort(a, true);
    cout << "Mang sau khi sap xep tang dan: ";
    for (int i = 0; i < MAX; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
      InterchangeSort(a, false);
    cout << "Mang sau khi sap xep giam dan: ";
    for (int i = 0; i < MAX; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
    
    index = BinarySearch(a, x);
    if (index != -1) {
        cout << "Tim thay " << x << " tai vi tri " << index << " bang Binary Search" << endl;
    } else {
        cout << x << " khong tim thay bang Binary Search" << endl;
    }
	
	SelectionSort(a);
    cout << "Mang sau khi sap xep tang dan bang Selection Sort: ";
    for (int i = 0; i < MAX; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
    
    QuickSort(a, 0, MAX - 1);
    cout << "Mang sau khi sap xep tang dan bang Quick Sort: ";
    for (int i = 0; i < MAX; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
	return 0;
	
}
