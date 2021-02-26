#include "pch.h"
#include "gtest/gtest.h"
#include "Forest.h"
using namespace std;


TEST(PreProcessingTest, TestOne) {

	// Test initial permutation
	string FilePath = "rawDataset.csv";
	LinkedList<string> Dataset = preProcessing(FilePath);
	string trueRow0 = "Excellent,Excellent,Excellent,Excellent,Average,Excellent,Good,Good,Good,Excellent,Excellent,Excellent,Good,Unknown,Excellent,Good,Excellent,Excellent";
	string trueRow4 = "Average,Average,Average,Average,Good,Unknown,Unknown,Bad,Bad,Good,Bad,Average,Unknown,Worst,Unknown,Average,Excellent,Worst";

	string Row0 = Dataset.get(0);
	string Row4 = Dataset.get(4);
	for (int i = 0; i < 150; i++)
	{
		EXPECT_EQ(trueRow0[i], Row0[i]);
	}
	for (int i = 0; i < 123; i++)
	{
		EXPECT_EQ(trueRow4[i], Row4[i]);
	}

}


TEST(EntropyOnFeatureTest, TestTwo) {

	string Array[] = { "Excellent,Normal","Excellent,Normal","Excellent,Normal","Excellent,High","Good,Normal","Good,Normal","Good,Normal","Good,Normal","Good,High","Good,High","Poor,High","Poor,High","Poor,High","Poor,High" };

	LinkedList<string> Dataset;

	for (int i = 0; i < 14; i++) {
		Dataset.insert(Array[i]);
	}
	float trueEntropy = 0.6253491072973906;
	int featureIndex = 0;
	float Entropy = calculateEntropyOnFeature(Dataset, featureIndex);

	float errorAllowed = 0.1;
	EXPECT_LT(Entropy, trueEntropy + errorAllowed);
	EXPECT_GT(Entropy, trueEntropy - errorAllowed);
}


TEST(totalEntropyTest, TestThree) {

	string Array[] = { "Excellent,Normal","Excellent,Normal","Excellent,Normal","Excellent,High","Good,Normal","Good,Normal","Good,Normal","Good,Normal","Good,High","Good,High","Poor,High","Poor,High","Poor,High","Poor,High" };
	LinkedList<string> Dataset;
	for (int i = 0; i < 14; i++) {
		Dataset.insert(Array[i]);
	}
	float trueTotalEntropy = 1.0;
	float TotalEntropy = calculateTotalEntropy(Dataset);
	float errorAllowed = 0.1;
	EXPECT_LT(TotalEntropy, trueTotalEntropy + errorAllowed);
	EXPECT_GT(TotalEntropy, trueTotalEntropy - errorAllowed);
}


TEST(inOrderTraversal, TestFour) {

	string trainFilePath = "trainDataset.csv";
	LinkedList<string> trainDataset = read_csv(trainFilePath);
	Tree<string> tree;
	int start = 0;
	int windowSize = 5;
	tree.build_tree(trainDataset, start, 5);
	string trueInOrderTraversed = "4,14,0,0,4,0,5,1,3,0,4";
	string inOrderTraversed = tree.inOrderTraversal();
	for (int i = 0; i < 22; i++)
	{
		EXPECT_EQ(trueInOrderTraversed[i], inOrderTraversed[i]);
	}
}


TEST(preOrderTraversal, TestFive) {

	string trainFilePath = "trainDataset.csv";
	LinkedList<string> trainDataset = read_csv(trainFilePath);
	Tree<string> tree;
	int start = 0;
	int windowSize = 5;
	tree.build_tree(trainDataset, start, 5);
	string truePreOrderTraversed = "3,4,14,4,0,0,5,0,1,4,0";
	string preOrderTraversed = tree.preOrderTraversal();
	for (int i = 0; i < 22; i++)
	{
		EXPECT_EQ(truePreOrderTraversed[i], preOrderTraversed[i]);
	}
}


TEST(postOrderTraversal, TestSix) {

	string trainFilePath = "trainDataset.csv";
	LinkedList<string> trainDataset = read_csv(trainFilePath);
	Tree<string> tree;
	int start = 0;
	int windowSize = 5;
	tree.build_tree(trainDataset, start, 5);
	string truePostOrderTraversed = "4,14,0,0,4,0,5,1,0,4,3";
	string postOrderTraversed = tree.postOrderTraversal();
	for (int i = 0; i < 22; i++)
	{
		EXPECT_EQ(truePostOrderTraversed[i], postOrderTraversed[i]);
	}
}



TEST(treePredictOne, TestSeven) {
	string trainFilePath = "trainDataset.csv";
	string testFilePath = "testDataset.csv";

	LinkedList<string> trainDataset = read_csv(trainFilePath);
	LinkedList<string> testDataset = read_csv(testFilePath);

	Tree<string> tree;
	int start = 0;
	int windowSize = 5;
	tree.build_tree(trainDataset, start, 5);


	LinkedList<string> truePredictions;
	LinkedList<string> Predictions;

	truePredictions.insert("Excellent");
	truePredictions.insert("Worst");
	truePredictions.insert("Good");

	Predictions.insert(tree.predictOne(testDataset, 0));
	Predictions.insert(tree.predictOne(testDataset, 2));
	Predictions.insert(tree.predictOne(testDataset, 3));


	string trueLabel = "";
	string prediction = "";

	EXPECT_EQ(truePredictions.getLength(), Predictions.getLength());
	for (int i = 0; i < truePredictions.getLength(); i++)
	{
		trueLabel = truePredictions.get(i);
		prediction = Predictions.get(i);
		for (int j = 0; j < trueLabel.size(); j++) {
			EXPECT_EQ(trueLabel[j], prediction[j]);
		}
	}
}


TEST(treePredictAll, TestEight) {
	string trainFilePath = "trainDataset.csv";
	string testFilePath = "testDataset.csv";

	LinkedList<string> trainDataset = read_csv(trainFilePath);
	LinkedList<string> testDataset = read_csv(testFilePath);

	Tree<string> tree;
	int start = 0;
	int windowSize = 5;
	tree.build_tree(trainDataset, start, 5);
	string Array[] = { "Excellent","Average","Worst","Good","Worst","Worst","Good","Good","Excellent","Worst","Good","Excellent","Excellent","Excellent","Excellent","Good","Good","Excellent","Good","Average" };

	LinkedList<string> truePredictions;
	for (int i = 0; i < 20; i++) {
		truePredictions.insert(Array[i]);
	}

	LinkedList<string> Predictions = tree.predictAll(testDataset);

	string trueLabel = "";
	string prediction = "";
	EXPECT_EQ(truePredictions.getLength(), Predictions.getLength());
	for (int i = 0; i < truePredictions.getLength(); i++)
	{
		trueLabel = truePredictions.get(i);
		prediction = Predictions.get(i);
		for (int j = 0; j < trueLabel.size(); j++) {
			EXPECT_EQ(trueLabel[j], prediction[j]);
		}
	}

}


TEST(forestPredictOne, TestNine) {
	string trainFilePath = "trainDataset.csv";
	string testFilePath = "testDataset.csv";

	LinkedList<string> trainDataset = read_csv(trainFilePath);
	LinkedList<string> testDataset = read_csv(testFilePath);

	int windowSize = 5;
	int NTrees = 5;
	int stepSize = 2;
	Forest<string> forest(NTrees, windowSize, stepSize);
	forest.build_forest(trainDataset);

	LinkedList<string> truePrediction0;
	LinkedList<string> truePrediction1;
	LinkedList<string> truePrediction7;

	truePrediction0.insert("Excellent");
	truePrediction1.insert("Average");
	truePrediction7.insert("Good");

	LinkedList<string> Prediction0 = forest.predictOne(testDataset, 0);
	LinkedList<string> Prediction1 = forest.predictOne(testDataset, 1);
	LinkedList<string> Prediction7 = forest.predictOne(testDataset, 7);

	string trueLabel = "";
	string prediction = "";

	EXPECT_EQ(truePrediction0.getLength(), Prediction0.getLength());
	for (int i = 0; i < truePrediction0.getLength(); i++)
	{
		trueLabel = truePrediction0.get(i);
		prediction = Prediction0.get(i);
		for (int j = 0; j < trueLabel.size(); j++) {
			EXPECT_EQ(trueLabel[j], prediction[j]);
		}
	}

	EXPECT_EQ(truePrediction1.getLength(), Prediction1.getLength());
	for (int i = 0; i < truePrediction1.getLength(); i++)
	{
		trueLabel = truePrediction1.get(i);
		prediction = Prediction1.get(i);
		for (int j = 0; j < trueLabel.size(); j++) {
			EXPECT_EQ(trueLabel[j], prediction[j]);
		}
	}

	EXPECT_EQ(truePrediction7.getLength(), Prediction7.getLength());
	for (int i = 0; i < truePrediction7.getLength(); i++)
	{
		trueLabel = truePrediction7.get(i);
		prediction = Prediction7.get(i);
		for (int j = 0; j < trueLabel.size(); j++) {
			EXPECT_EQ(trueLabel[j], prediction[j]);
		}
	}
}


TEST(forestPredictAll, TestTen) {
	string trainFilePath = "trainDataset.csv";
	string testFilePath = "testDataset.csv";

	LinkedList<string> trainDataset = read_csv(trainFilePath);
	LinkedList<string> testDataset = read_csv(testFilePath);

	int windowSize = 5;
	int NTrees = 5;
	int stepSize = 2;
	Forest<string> forest(NTrees, windowSize, stepSize);
	forest.build_forest(trainDataset);

	string Array[20][1] = { {"Excellent"},{"Average"},{"Worst"},{"Good"},{"Worst"},{"Worst"},{"Good"},{"Good"},{"Excellent"},{"Good"},{"Excellent"},{"Excellent"},{"Excellent"},{"Excellent"},{"Excellent"},{"Average"},{"Excellent"},{"Excellent"},{"Good"},{"Average"} };
	int Lengths[20] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	LinkedList<LinkedList<string>> truePrediction;

	for (int i = 0; i < 20; i++) {
		truePrediction.insert(LinkedList<string>());
		for (int j = 0; j < Lengths[i]; j++) {
			truePrediction.get(i).insert(Array[i][j]);
		}
	}

	LinkedList<LinkedList<string>> Predictions = forest.predictAll(testDataset);
	string trueLabel = "";
	string prediction = "";

	EXPECT_EQ(truePrediction.getLength(), Predictions.getLength());
	for (int i = 0; i < truePrediction.getLength(); i++)
	{
		EXPECT_EQ(truePrediction.get(i).getLength(), Predictions.get(i).getLength());
		for (int j = 0; j < truePrediction.get(i).getLength(); j++) {
			trueLabel = truePrediction.get(i).get(j);
			prediction = Predictions.get(i).get(j);
			for (int k = 0; k < trueLabel.size(); k++) {
				EXPECT_EQ(trueLabel[k], prediction[k]);
			}
		}
	}
}


TEST(checkAccuracy, TestEleven) {
	string trainFilePath = "trainDataset.csv";
	string testFilePath = "testDataset.csv";

	LinkedList<string> trainDataset = read_csv(trainFilePath);
	LinkedList<string> testDataset = read_csv(testFilePath);

	int windowSize = 5;
	int NTrees = 5;
	int stepSize = 2;
	Forest<string> forest(NTrees, windowSize, stepSize);
	forest.build_forest(trainDataset);
	float trueAccuracy = 0.5;
	float Accuracy = forest.accuracy(testDataset);
	float errorAllowed = 0.001;
	EXPECT_LT(Accuracy, trueAccuracy + errorAllowed);
	EXPECT_GT(Accuracy, trueAccuracy - errorAllowed);

}