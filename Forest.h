#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

template <typename Type>
struct LinkedList {

    template <typename TypeValue>
    struct Node {
        TypeValue value;
        Node<TypeValue>* Next;
    };
    int Length = 0;
    Node<Type>* Head = NULL;

    //Insert val in the LinkedList
    void insert(Type val) {
        Node<Type>* temp = new Node<Type>;
        temp->value = val;
        temp->Next = NULL;
        if (Head == NULL)
            Head = temp;
        else {
            Node<Type>* curr = Head;
            while (curr->Next != NULL) {
                curr = curr->Next;
            }
            curr->Next = temp;
        }
        Length++;
    }

    //This function returns value at i'th index
    Type& get(int Index) {
        Node<Type>* curr = Head;
        int i = 0;
        while (i != Index) {
            curr = curr->Next;
            i++;
        }
        return curr->value;
    }

    void display() {
        Node<Type>* curr = Head;
        while (curr != NULL) {
            cout << curr->value << endl;
            curr = curr->Next;
        }
    }
    //Function to return length of LinkedList
    int getLength() {
        return Length;
    }

};

template <typename Type>
struct Course {
    Type courseCode, courseTitle, CrHours, Grade, GPA, Label;
    Course() {
        courseCode = courseTitle = CrHours = Grade = GPA = Label = "";
    }
    void Reset() {
        courseCode = courseTitle = CrHours = Grade = GPA = Label = "";
    }
    void Set(Type cc, Type ct, Type crh, Type grade, Type gpa) {
        courseCode = cc;
        courseTitle = ct;
        CrHours = crh;
        Grade = grade;
        GPA = gpa;
    }
    Course(const Course& c) {
        courseCode = c.courseCode;
        courseTitle = c.courseTitle;
        CrHours = c.CrHours;
        Grade = c.Grade;
        GPA = c.GPA;
    }
};

template <typename Type>
struct Student {
    Type rollNo, Semester, SGPA, CGPA, Warning, CGPA_Label, Warning_Label;
    Course<Type> courses[16];
    Student() {
        rollNo = Semester = SGPA = CGPA = Warning = CGPA_Label = Warning_Label = "";
    }

    void sortCourses() {
        for (int i = 0; i < 15; i++) {
            for (int j = i + 1; j < 15; j++) {
                if (courses[i].courseCode > courses[j].courseCode) {
                    Course<Type> temp = courses[i];
                    courses[i] = courses[j];
                    courses[j] = temp;
                }
            }
        }
    }

    void generateLabels() {
        for (int i = 0; i < 16; i++) {
            if (courses[i].Grade == "A" || courses[i].Grade == "A+" || courses[i].Grade == "A-")
                courses[i].Label = "Excellent";
            else if (courses[i].Grade == "B" || courses[i].Grade == "B+" || courses[i].Grade == "B-")
                courses[i].Label = "Good";
            else if (courses[i].Grade == "C" || courses[i].Grade == "C+" || courses[i].Grade == "C-")
                courses[i].Label = "Average";
            else if (courses[i].Grade == "D" || courses[i].Grade == "D+")
                courses[i].Label = "Bad";
            else if (courses[i].Grade == "F" || courses[i].Grade == "W")
                courses[i].Label = "Worst";
            else
                courses[i].Label = "Unknown";
        }

        if (Warning == "2" || Warning == "3")
            Warning_Label = "Worst";
        else if (Warning == "1")
            Warning_Label = "Average";
        else if (Warning == "0")
            Warning_Label = "Excellent";

        if (stod(CGPA) >= 3.67)
            CGPA_Label = "Excellent";
        else if (stod(CGPA) < 3.67 && stod(CGPA) >= 2.67)
            CGPA_Label = "Good";
        else if (stod(CGPA) < 2.67 && stod(CGPA) >= 1.67)
            CGPA_Label = "Average";
        else if (stod(CGPA) < 1.67 && stod(CGPA) >= 1.0)
            CGPA_Label = "Bad";
        else if (stod(CGPA) < 1.0)
            CGPA_Label = "Worst";
    }

};

//This function takes a File path as an input, preprocesses it and then returns a LinkedList of strings in csv format
//This function also writes the rows in a csv file i.e. preProcessed.csv
LinkedList<string> preProcessing(string FilePath) {
    LinkedList<string> l;
    ifstream in;
    in.open(FilePath);
    string rollNo, Semester, courseCode, courseTitle, CrHours, Grade, GPA, SGPA, CGPA, Warning;
    Student<string> s;
    int i = 0;
    getline(in, rollNo);
    while (getline(in, rollNo, ','))
    {
        getline(in, Semester, ',');
        getline(in, courseCode, ',');
        getline(in, courseTitle, ',');
        getline(in, CrHours, ',');
        getline(in, Grade, ',');
        getline(in, GPA, ',');
        getline(in, SGPA, ',');
        getline(in, CGPA, ',');
        getline(in, Warning, '\n');

        int flag = 0;
        if (s.rollNo == "") {
            s.rollNo = rollNo;
            s.Semester = Semester;

            s.CGPA = CGPA;
            s.SGPA = SGPA;
            s.Warning = Warning;
        }

        else if (s.rollNo != rollNo) {
            s.sortCourses();
            s.generateLabels();

            // Check if Data Structures has been studied or not
            int flag = 1;
            if (s.courses[15].Label == "Unknown") {
                flag = 0;
            }

            if (flag == 1) {
                string str = "";
                for (int j = 0; j < 15; j++) {
                    str += s.courses[j].Label + ",";
                }
                str += s.CGPA_Label + ",";
                str += s.Warning_Label + ",";
                str += s.courses[15].Label;
                l.insert(str);
            }

            // Data for new Roll Number
            s.rollNo = rollNo;
            s.Semester = Semester;
            s.SGPA = SGPA;
            s.Warning = Warning;
            i = 0;

            // Reset the courses array for new Roll Number
            for (int j = 0; j < 16; j++) {
                s.courses[j].Reset();
            }
        }

        if (courseCode == "CL118" || courseCode == "CS118" || courseCode == "CL217" || courseCode == "CS217" || courseCode == "EE182" || courseCode == "EE227" || courseCode == "EL227" || courseCode == "MT104" || courseCode == "MT119" || courseCode == "MT224" || courseCode == "SS101" || courseCode == "SL101" || courseCode == "SS111" || courseCode == "SS113" || courseCode == "SS122") {
            for (int j = 0; j < 15; j++) {
                if (s.courses[j].courseCode == courseCode) {
                    s.courses[j].Grade = Grade;
                    s.courses[j].GPA = GPA;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                if (CGPA != "0")
                    s.CGPA = CGPA;
                s.courses[i++].Set(courseCode, courseTitle, CrHours, Grade, GPA);
            }
        }
        if (courseCode == "CS201") {
            if (CGPA != "0")
                s.CGPA = CGPA;
            s.courses[15].Set(courseCode, courseTitle, CrHours, Grade, GPA);
        }
    }
    in.close();

    s.sortCourses();
    s.generateLabels();
    int flag = 1;
    if (s.courses[15].Label == "Unknown") {
        flag = 0;
    }
    if (flag == 1) {
        string str = "";
        for (int j = 0; j < 15; j++) {
            str += s.courses[j].Label + ",";
        }
        str += s.CGPA_Label + ",";
        str += s.Warning_Label + ",";
        str += s.courses[15].Label;
        l.insert(str);
    }
    ofstream out;
    out.open("preProcessed.csv");
    for (int i = 0; i < l.Length; i++) {
        out << l.get(i) << endl;
    }
    out.close();

    return l;
}

//This function takes path of a preprocessed csv file and loads it into LinkedList
LinkedList<string> read_csv(string FilePath) {
    LinkedList<string> l;
    ifstream in;
    in.open(FilePath);
    string s;
    getline(in, s);
    while (getline(in, s)) {
        l.insert(s);
    }
    in.close();
    return l;
}

// function to return index of respective labels
int Index(string s) {
    if (s == "Excellent")
        return 0;
    else if (s == "Good" || s == "High")
        return 1;
    else if (s == "Average" || s == "Normal")
        return 2;
    else if (s == "Bad" || s == "Poor")
        return 3;
    else if (s == "Worst")
        return 4;
    else if (s == "Unknown")
        return 5;
}

//This function takes any specific Feature and calculate Entropy.
float calculateEntropyOnFeature(LinkedList<string> Dataset, int FeatureIndex) {
    string s = Dataset.get(0);
    string* str1 = new string[Dataset.Length];
    for (int i = 0; i < Dataset.Length; i++) {  // load data to string from linked list
        str1[i] = Dataset.get(i);
    }

    int cols = 1;
    for (int i = 0; s[i] != '\0'; i++) { // counting columns in dataset
        if (s[i] == ',') {
            cols++;
        }
    }

    string** str2 = new string * [Dataset.Length];
    for (int i = 0; i < Dataset.Length; i++)
        str2[i] = new string[cols];
    string* str3 = new string[cols];
    string word = "";
    for (int i = 0; i < Dataset.Length; i++) {  // seperating the labels
        int l = 0;
        word = "";
        for (int k = 0; str1[i][k] != '\0'; k++) {
            if (str1[i][k] == ',') {
                str3[l] = word;
                word = "";
                l++;
            }
            else {
                word += str1[i][k];
            }
        }
        str3[l] = word;
        for (int j = 0; j < cols; j++) {
            str2[i][j] = str3[j];
        }
    }

    // counting labels
    float counts[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++)
            counts[i][j] = 0;
    }

    int m = 0, n = 0;
    for (int i = 0; i < Dataset.Length; i++) {
        static string temp1 = str2[i][FeatureIndex];
        static string temp2 = str2[i][cols - 1];
        n = Index(temp2);
        m = Index(temp1);
        if (temp1 == str2[i][FeatureIndex]) {
            if (temp2 == str2[i][cols - 1]) {
                counts[m][n]++;
            }

            else if (temp2 != str2[i][cols - 1]) {
                temp2 = str2[i][cols - 1];
                n = Index(temp2);
                counts[m][n]++;
            }
        }

        else if (temp1 != str2[i][FeatureIndex]) {
            temp1 = str2[i][FeatureIndex];
            temp2 = str2[i][cols - 1];
            n = Index(temp2);
            m = Index(temp1);
            counts[m][n]++;
        }

    }

    // calculating Entropy
    float Entropy = 0;
    for (int i = 0; i < 6; i++) {
        float total = 0, e = 0;
        for (int j = 0; j < 6; j++) {
            total += counts[i][j];
        }
        for (int j = 0; j < 6; j++) {
            if (total != 0 && counts[i][j] != 0)
                e += (counts[i][j] / total) * log2((counts[i][j] / total));
        }
        e *= -1;
        Entropy += (total / Dataset.Length) * e;
    }

    for (int i = 0; i < Dataset.Length; i++)
        delete[] str2[i];
    delete[] str2;
    delete[] str1;
    delete[] str3;
    return Entropy;

}


//This function takes Labels as an input and calculate Total Entropy.
float calculateTotalEntropy(LinkedList<string> Dataset) {
    if (Dataset.Length == 0)
        return 0.0;

    string s = Dataset.get(0);
    string* str1 = new string[Dataset.Length];
    for (int i = 0; i < Dataset.Length; i++) {  // load data to string from linked list
        str1[i] = Dataset.get(i);
    }

    int cols = 1;
    for (int i = 0; s[i] != '\0'; i++) {  // counting columns in dataset
        if (s[i] == ',') {
            cols++;
        }
    }
    string** str2 = new string * [Dataset.Length];
    for (int i = 0; i < Dataset.Length; i++)
        str2[i] = new string[cols];
    string* str3 = new string[cols];
    string word = "";
    for (int i = 0; i < Dataset.Length; i++) { // seperating the labels
        int l = 0;
        word = "";
        for (int k = 0; str1[i][k] != '\0'; k++) {
            if (str1[i][k] == ',') {
                str3[l] = word;
                word = "";
                l++;
            }
            else {
                word += str1[i][k];
            }
        }
        str3[l] = word;
        for (int j = 0; j < cols; j++) {
            str2[i][j] = str3[j];
        }
    }

    // counting labels
    float counts[6];
    for (int i = 0; i < 6; i++) {
        counts[i] = 0;
    }

    for (int i = 0; i < Dataset.Length; i++) {
        for (int j = i + 1; j < Dataset.Length; j++) {
            if (str2[i][cols - 1] > str2[j][cols - 1]) {
                string temp = str2[i][cols - 1];
                str2[i][cols - 1] = str2[j][cols - 1];
                str2[j][cols - 1] = temp;
            }
        }
    }

    int m = 0;
    for (int i = 0; i < Dataset.Length; i++) {
        static string temp = str2[i][cols - 1];
        m = Index(temp);
        if (temp == str2[i][cols - 1]) {
            counts[m]++;
        }

        else if (temp != str2[i][cols - 1]) {
            temp = str2[i][cols - 1];
            m = Index(temp);
            counts[m]++;
        }
    }

    // calculating Entropy
    float Entropy = 0, total = Dataset.Length;
    for (int i = 0; i < 6; i++) {
        if (counts[i] != 0)
            Entropy += (counts[i] / total) * log2((counts[i] / total));
    }

    for (int i = 0; i < Dataset.Length; i++)
        delete[] str2[i];
    delete[] str2;
    delete[] str1;
    delete[] str3;

    return -1 * Entropy;
}

// function to partition the dataset after each splitting
void partitionDataset(LinkedList<string> l[6], string** str2, int featureIndex, LinkedList<string> trainDataset) {
    string temp = "";
    bool flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0, flag6 = 0;
    for (int i = 0; i < trainDataset.Length; i++) {
        for (int j = 0; j < 18; j++) {
            if (j == featureIndex) {
                if (str2[i][j] == "Excellent")
                    flag1 = 1;
                else if (str2[i][j] == "Good")
                    flag2 = 1;
                else if (str2[i][j] == "Average")
                    flag3 = 1;
                else if (str2[i][j] == "Bad")
                    flag4 = 1;
                else if (str2[i][j] == "Worst")
                    flag5 = 1;
                else if (str2[i][j] == "Unknown")
                    flag6 = 1;
            }
            temp += str2[i][j];
            if (j != 17) {
                temp += ",";
            }
        }

        if (flag1) {
            l[0].insert(temp);
            flag1 = 0;
        }
        else if (flag2) {
            l[1].insert(temp);
            flag2 = 0;
        }
        else if (flag3) {
            l[2].insert(temp);
            flag3 = 0;
        }
        else if (flag4) {
            l[3].insert(temp);
            flag4 = 0;
        }
        else if (flag5) {
            l[4].insert(temp);
            flag5 = 0;
        }
        else if (flag6) {
            l[5].insert(temp);
            flag6 = 0;
        }

        temp = "";
    }
}

// function to convert linked link to 2d string array
void to2Dstring(string** str2, LinkedList<string> Dataset) {
    string* str1 = new string[Dataset.Length];
    for (int i = 0; i < Dataset.Length; i++) {  // load data to string from linked list
        str1[i] = Dataset.get(i);
    }

    string str3[18];
    string word = "";
    for (int i = 0; i < Dataset.Length; i++) {  // seperating the labels
        int l = 0;
        word = "";
        for (int k = 0; str1[i][k] != '\0'; k++) {
            if (str1[i][k] == ',') {
                str3[l] = word;
                word = "";
                l++;
            }
            else {
                word += str1[i][k];
            }
        }
        str3[l] = word;
        for (int j = 0; j < 18; j++) {
            str2[i][j] = str3[j];
        }
    }
    delete[] str1;
}

//Data Structure to maintain Nodes in a Tree
template<typename T>
struct treeNode {
    T data;
    treeNode<T>* Excellent;
    treeNode<T>* Good;
    treeNode<T>* Average;
    treeNode<T>* Bad;
    treeNode<T>* Worst;
    treeNode<T>* Unknown;
};

//Data Structure to maintain Tree for training, predictions and traversal
template <typename T>
struct Tree {
    treeNode<T>* Root;
    void expand_tree(LinkedList<T> trainDataset, int index, treeNode<T>* Node, string label = "") {
        int featureIndex = 0;
        float totalEntropy = calculateTotalEntropy(trainDataset);
        float InfoGain, MaxGain = 0;
        if (totalEntropy != 0) {
            for (int i = 0; i < 17; i++) {
                float featureEntropy = calculateEntropyOnFeature(trainDataset, i);
                InfoGain = totalEntropy - featureEntropy;
                if (MaxGain < InfoGain) {
                    MaxGain = InfoGain;
                    featureIndex = i;
                }
            }
        }

        treeNode<T>* temp = new treeNode<T>;
        if (label != "")
            temp->data = label;
        else
            temp->data = to_string(featureIndex);
        temp->Excellent = NULL;
        temp->Good = NULL;
        temp->Average = NULL;
        temp->Bad = NULL;
        temp->Worst = NULL;
        temp->Unknown = NULL;


        if (index == 0) {
            treeNode<T>* curr = Node;
            while (curr->Excellent != NULL) {
                curr = curr->Excellent;
            }
            curr->Excellent = temp;

        }
        else if (index == 1) {
            treeNode<T>* curr = Node;
            while (curr->Good != NULL) {
                curr = curr->Good;
            }
            curr->Good = temp;

        }
        else if (index == 2) {
            treeNode<T>* curr = Node;
            while (curr->Average != NULL) {
                curr = curr->Average;
            }
            curr->Average = temp;

        }
        else if (index == 3) {
            treeNode<T>* curr = Node;
            while (curr->Bad != NULL) {
                curr = curr->Bad;
            }
            curr->Bad = temp;

        }
        else if (index == 4) {
            treeNode<T>* curr = Node;
            while (curr->Worst != NULL) {
                curr = curr->Worst;
            }
            curr->Worst = temp;

        }
        else if (index == 5) {
            treeNode<T>* curr = Node;
            while (curr->Unknown != NULL) {
                curr = curr->Unknown;
            }
            curr->Unknown = temp;

        }
        if (label != "")
            return;

        string** str2d = new string * [trainDataset.Length];
        for (int i = 0; i < trainDataset.Length; i++)
            str2d[i] = new string[18];

        LinkedList<T> l[6];
        to2Dstring(str2d, trainDataset);
        partitionDataset(l, str2d, featureIndex, trainDataset);

        string finalLabel = "";
        for (int i = 0; i < 6; i++) {
            totalEntropy = calculateTotalEntropy(l[i]);
            if (totalEntropy != 0) {
                expand_tree(l[i], i, temp);
            }
            else if (totalEntropy == 0 && l[i].Length != 0) {
                to2Dstring(str2d, l[i]);
                finalLabel = str2d[0][17];
                expand_tree(l[i], i, temp, finalLabel);
            }
        }

        for (int i = 0; i < trainDataset.Length; i++)
            delete[] str2d[i];
        delete[] str2d;
    }

    void build_tree(LinkedList<T> trainDataset, int start, int WindowSize) {
        int featureIndex = 0, end = WindowSize + start;
        float totalEntropy = calculateTotalEntropy(trainDataset);
        float InfoGain, MaxGain = 0;
        for (int i = start; i < end; i++) {
            float featureEntropy = calculateEntropyOnFeature(trainDataset, i);
            InfoGain = totalEntropy - featureEntropy;
            if (MaxGain < InfoGain) {
                MaxGain = InfoGain;
                featureIndex = i;
            }
        }

        treeNode<T>* temp = new treeNode<T>;
        temp->data = to_string(featureIndex);
        temp->Excellent = NULL;
        temp->Good = NULL;
        temp->Average = NULL;
        temp->Bad = NULL;
        temp->Worst = NULL;
        temp->Unknown = NULL;
        Root = temp;

        string** str2d = new string * [trainDataset.Length];
        for (int i = 0; i < trainDataset.Length; i++)
            str2d[i] = new string[18];

        LinkedList<T> l[6];
        to2Dstring(str2d, trainDataset);
        partitionDataset(l, str2d, featureIndex, trainDataset);

        string finalLabel = "";
        for (int i = 0; i < 6; i++) {
            totalEntropy = calculateTotalEntropy(l[i]);
            if (totalEntropy != 0) {
                expand_tree(l[i], i, Root);
            }
            else if (totalEntropy == 0 && l[i].Length != 0) {
                to2Dstring(str2d, l[i]);
                finalLabel = str2d[0][17];
                expand_tree(l[i], i, Root, finalLabel);
            }
        }

        for (int i = 0; i < trainDataset.Length; i++)
            delete[] str2d[i];
        delete[] str2d;
    }

    //Takes a testDataset and rowIndex as input and returns a potential string i.e. 'Good'
    T predictOne(LinkedList<T> testDataset, int rowIndex) {
        string** str2d = new string * [testDataset.Length];
        for (int i = 0; i < testDataset.Length; i++)
            str2d[i] = new string[18];

        to2Dstring(str2d, testDataset);
        treeNode<T>* Node = Root;
        while (Node->Excellent != NULL || Node->Good != NULL || Node->Average != NULL || Node->Bad != NULL || Node->Worst != NULL || Node->Unknown != NULL) {
            if (str2d[rowIndex][stoi(Node->data)] == "Excellent")
                Node = Node->Excellent;
            else if (str2d[rowIndex][stoi(Node->data)] == "Good")
                Node = Node->Good;
            else if (str2d[rowIndex][stoi(Node->data)] == "Average")
                Node = Node->Average;
            else if (str2d[rowIndex][stoi(Node->data)] == "Bad")
                Node = Node->Bad;
            else if (str2d[rowIndex][stoi(Node->data)] == "Worst") {
                Node = Node->Worst;
            }
            else if (str2d[rowIndex][stoi(Node->data)] == "Unknown")
                Node = Node->Unknown;

            if (Node == NULL)
                return "Unknown";
        }

        for (int i = 0; i < testDataset.Length; i++)
            delete[] str2d[i];
        delete[] str2d;

        return Node->data;
    }

    //Takes a testDataset as input and returns a potential predictions as LinkedList<string> i.e. {'Good','Excellent','Notfound'}
    LinkedList<T> predictAll(LinkedList<T> testDataset) {
        LinkedList<T> l;
        for (int i = 0; i < testDataset.Length; i++) {
            l.insert(predictOne(testDataset, i));
        }
        return l;
    }

    //This function computes accuracy after training
    float accuracy(LinkedList<T> testDataset) {
        LinkedList<T> l;
        for (int i = 0; i < testDataset.Length; i++) {
            l.insert(predictOne(testDataset, i));
        }

        string** str2d = new string * [testDataset.Length];
        for (int i = 0; i < testDataset.Length; i++)
            str2d[i] = new string[18];
        to2Dstring(str2d, testDataset);

        float truePos = 0;
        float total = testDataset.Length;
        for (int i = 0; i < testDataset.Length; i++) {
            if (l.get(i) == str2d[i][17])
                truePos++;
        }
        float result = truePos / total;

        for (int i = 0; i < testDataset.Length; i++)
            delete[] str2d[i];
        delete[] str2d;

        return result;
    }

    string returnpreOrder(treeNode<T>* n) {
        static string s = "";
        string str = "";
        if (n != NULL) {
            str = n->data;
            if (str.size() <= 2)
                s += str + ",";
            returnpreOrder(n->Excellent);
            returnpreOrder(n->Good);
            returnpreOrder(n->Average);
            returnpreOrder(n->Bad);
            returnpreOrder(n->Worst);
            returnpreOrder(n->Unknown);
        }
        return s;
    }

    //This function returns string in csv format i.e. "1,16,2,9" after traversing in preOrder fashion.
    //Check Test Case for better understanding of output
    string preOrderTraversal() {
        string s = returnpreOrder(Root);
        s.pop_back();   // remove last comma
        return s;
    }

    string returninOrder(treeNode<T>* n) {
        static string s = "";
        string str = "";
        if (n != NULL) {
            returninOrder(n->Excellent);
            returninOrder(n->Good);
            returninOrder(n->Average);
            returninOrder(n->Bad);
            returninOrder(n->Worst);
            str = n->data;
            if (str.size() <= 2)
                s += str + ",";
            returninOrder(n->Unknown);

        }
        return s;
    }

    //This function returns string in csv format i.e. "1,16,2,9" after traversing in inOrder fashion
    //Check Test Case for better understanding of output
    string inOrderTraversal() {
        string s = returninOrder(Root);
        s.pop_back();   // remove last comma
        return s;
    }

    string returnpostOrder(treeNode<T>* n) {
        static string s = "";
        string str = "";
        if (n != NULL) {
            returnpostOrder(n->Excellent);
            returnpostOrder(n->Good);
            returnpostOrder(n->Average);
            returnpostOrder(n->Bad);
            returnpostOrder(n->Worst);
            returnpostOrder(n->Unknown);
            str = n->data;
            if (str.size() <= 2)
                s += str + ",";
        }
        return s;
    }

    //This function returns string in csv format i.e. "1,16,2,9" after traversing in postOrder fashion
    //Check Test Case for better understanding of output
    string postOrderTraversal() {
        string s = returnpostOrder(Root);
        s.pop_back();   // remove last comma
        return s;
    }
};


//Data Structure to maintain Multiple Trees for training and predictions
template <typename T>
struct Forest {
    Tree<T>* trees;
    int NoofTrees, window, steps;
    //Constructor to set some data members 
    Forest(int NTrees, int WindowSize, int stepSize) {
        NoofTrees = NTrees;
        trees = new Tree<T>[NoofTrees];
        window = WindowSize;
        steps = stepSize;
    }

    //This function calls train on each tree individually by following the sliding window logic and keeps track of those trees.
    void build_forest(LinkedList<T> trainDataset) {
        int start = 0;
        for (int i = 0; i < NoofTrees; i++) {
            trees[i].build_tree(trainDataset, start, window);
            start += steps;
            start = start % 17;
        }
    }

    //This function takes predictions on 1 entry of testDataset from all Trees and then merge them together, 
    //and only gives those entries whose occurence is maximum in that list and return that.
    LinkedList<T> predictOne(LinkedList<T> testDataset, int rowIndex) {
        LinkedList<T> l;
        string* s = new string[NoofTrees];
        for (int i = 0; i < NoofTrees; i++) {
            s[i] = trees[i].predictOne(testDataset, rowIndex);
        }

        for (int i = 0; i < NoofTrees; i++) {
            for (int j = i + 1; j < NoofTrees; j++) {
                if (s[i] > s[j]) {
                    string temp = s[i];
                    s[i] = s[j];
                    s[j] = temp;
                }
            }
        }
        int max = 0;
        int count = 1;
        string temp = s[0];
        int index;
        for (int i = 1; i < NoofTrees; i++) {
            if (temp == s[i])
                count++;

            if (temp != s[i]) {
                temp = s[i];
                count = 1;
            }
            if (max < count) {
                max = count;
                index = i;
            }

        }

        count = 1;
        temp = s[0];
        for (int i = 1; i < NoofTrees; i++) {
            if (temp == s[i])
                count++;

            if (temp != s[i]) {
                temp = s[i];
                count = 1;
            }
            if (max == count) {
                l.insert(s[i]);
            }
        }

        delete[] s;
        return l;
    }

    //This function takes predictions on all entries of testDataset from all Trees and then merge them together, 
    //and only gives those entries whose occurence is maximum in that list and return that.
    LinkedList<LinkedList<T>> predictAll(LinkedList<T> testDataset) {
        LinkedList<LinkedList<T>> l;
        for (int i = 0; i < testDataset.Length; i++) {
            l.insert(predictOne(testDataset, i));
        }
        return l;
    }

    float accuracy(LinkedList<T> testDataset) {
        LinkedList<LinkedList<T>> l = predictAll(testDataset);

        string** str2d = new string * [testDataset.Length];
        for (int i = 0; i < testDataset.Length; i++)
            str2d[i] = new string[18];
        to2Dstring(str2d, testDataset);

        float truePos = 0;
        float total = testDataset.Length;
        for (int i = 0; i < testDataset.Length; i++) {
            for (int j = 0; j < l.get(i).getLength(); j++) {
                if (l.get(i).get(j) == str2d[i][17])
                    truePos++;
            }
        }
        float result = truePos / total;

        for (int i = 0; i < testDataset.Length; i++)
            delete[] str2d[i];
        delete[] str2d;

        return result;
    }

};
