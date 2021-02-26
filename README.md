<h1 align="center">Predicting Grades using a Forest</h1>
<p>The project uses machine learning technique, i.e. &ldquo;Random&rdquo; Forest, to predict grades in Data Structures course using previous academic data. Following concepts are used in predicting the grades.</p>
<ol>
<li>Dataset preprocessing</li>
<li>Model training (generating a single tree, and a forest of trees)</li>
<li>Modal value finding</li>
<li>Tree traversals to display the trees</li>
<li>Model testing (predicting a single grade, and grades of several students in Data Structures)</li>
</ol>

<h2>1. Preprocessing of the dataset</h2>
<p>Consider the following dataset:</p>
<table style="width:100%">
  <tr>
    <th>Sr.No</th>
    <th>Semester</th>
    <th>CourseCode</th>
    <th>CourseTitle</th>
    <th>CreditHours</th>
    <th>Grade</th>
    <th>GradePoint</th>
    <th>SGPA</th>
    <th>CGPA</th>
    <th>Warning</th>
  </tr>

  <tr>
    <td>1</td>
    <td>Fall 2016</td>
    <td>MT104</td>
    <td>Linear Algebra</td>
    <td>3</td>
    <td>B</td>
    <td>3</td>
    <td>3.27</td>
    <td>3.27</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Fall 2016</td>
    <td>MT101</td>
    <td>Calculus-I</td>
    <td>3</td>
    <td>B+</td>
    <td>3.33</td>
    <td>3.27</td>
    <td>3.27</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Fall 2016</td>
    <td>CS101</td>
    <td>ITC</td>
    <td>3</td>
    <td>A</td>
    <td>4</td>
    <td>3.27</td>
    <td>3.27</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Fall 2016</td>
    <td>CL101</td>
    <td>ITC Lab</td>
    <td>1</td>
    <td>A+</td>
    <td>4</td>
    <td>3.27</td>
    <td>3.27</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Fall 2016</td>
    <td>EE182</td>
    <td>Basic Elective</td>
    <td>3</td>
    <td>C-</td>
    <td>1.67</td>
    <td>3.27</td>
    <td>3.27</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Fall 2016</td>
    <td>SL101</td>
    <td>English Language</td>
    <td>1</td>
    <td>A-</td>
    <td>3.67</td>
    <td>3.27</td>
    <td>3.27</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Fall 2016</td>
    <td>SS101</td>
    <td>English Language Lab</td>
    <td>3</td>
    <td>A+</td>
    <td>4</td>
    <td>3.27</td>
    <td>3.27</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Fall 2017</td>
    <td>CS201</td>
    <td>Data Structures</td>
    <td>3</td>
    <td>A</td>
    <td>4</td>
    <td>3.75</td>
    <td>3.57</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Spring 2017</td>
    <td>EE227</td>
    <td>Digital Logic and Design</td>
    <td>3</td>
    <td>A+</td>
    <td>4</td>
    <td>3.71</td>
    <td>3.49</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Spring 2017</td>
    <td>SS122</td>
    <td>English Composition</td>
    <td>3</td>
    <td>A</td>
    <td>4</td>
    <td>3.71</td>
    <td>3.49</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Spring 2017</td>
    <td>MT115</td>
    <td>Calculus-II</td>
    <td>3</td>
    <td>A-</td>
    <td>3.67</td>
    <td>3.71</td>
    <td>3.49</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Spring 2017</td>
    <td>SS111</td>
    <td>Islamic and Religious Studies</td>
    <td>3</td>
    <td>B</td>
    <td>3</td>
    <td>3.71</td>
    <td>3.49</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Spring 2017</td>
    <td>CS103</td>
    <td>Computer Programming</td>
    <td>3</td>
    <td>A</td>
    <td>4</td>
    <td>3.71</td>
    <td>3.49</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Spring 2017</td>
    <td>EL227</td>
    <td>Digital Logic and Design Lab</td>
    <td>1</td>
    <td>B</td>
    <td>3</td>
    <td>3.71</td>
    <td>3.49</td>
    <td>0</td>
  </tr>

  <tr>
    <td>1</td>
    <td>Spring 2017</td>
    <td>CL103</td>
    <td>Computer Programming Lab</td>
    <td>1</td>
    <td>A+</td>
    <td>4</td>
    <td>3.71</td>
    <td>3.49</td>
    <td>0</td>
  </tr>
</table>

<h3>1.1. Instructions for preprocessing</h3>
<p>At first the data in <b>rawDataset.csv</b> file is read and restructured by arranging each student's records in one line as shown below.</p>
<table style="width:100%">
  <tr>
    <th>Sr.No</th>
    <th>MT104</th>
    <th>MT119</th>
    <th>CS118</th>
    <th>CL118</th>
    <th>EE182</th>
    <th>SL101</th>
    <th>SS101</th>
    <th>EE227</th>
    <th>SS122</th>
    <th>MT224</th>
    <th>SS111</th>
    <th>CS217</th>    
    <th>EL227</th>
    <th>CL217</th>
    <th>CGPA</th>
    <th>Warning</th>
    <th>CS201(Data Stratures)</th>
  </tr>

  <tr>
    <td>1</td>
    <td>3</td>
    <td>3.33</td>
    <td>4</td>
    <td>4</td>
    <td>1.67</td>
    <td>3.67</td>
    <td>4</td>
    <td>4</td>
    <td>4</td>
    <td>3.67</td>
    <td>3</td>
    <td>4</td>
    <td>3</td>
    <td>4</td>
    <td>3.49</td>
    <td>0</td>
    <td>4</td>
  </tr>

  <tr>
    <td>2</td>
    <td>4</td>
    <td>4</td>
    <td>3.67</td>
    <td>4</td>
    <td>3.33</td>
    <td>3</td>
    <td>4</td>
    <td>4</td>
    <td>4</td>
    <td>4</td>
    <td>3.33</td>
    <td>4</td>
    <td>2.33</td>
    <td>4</td>
    <td>3.66</td>
    <td>0</td>
    <td>4</td>
  </tr>

  <tr>
    <td>3</td>
    <td>3.33</td>
    <td>2.67</td>
    <td>2.67</td>
    <td>3.33</td>
    <td>2.33</td>
    <td>3.33</td>
    <td>3</td>
    <td>3</td>
    <td>4</td>
    <td>3</td>
    <td>3.67</td>
    <td>3.67</td>
    <td>3</td>
    <td>4</td>
    <td>3.21</td>
    <td>0</td>
    <td>3.33</td>
  </tr>
</table>

<p>Each student record (feature vector) consists of his scores of all subjects of the first two semesters, CGPA, and Warning, where CS201-Data Structures is treated as a label or target class. The sequence of the course codes is sorted alphabetically to match <b>trainDataset.csv</b> file. From the entire dataset, only those students who have studied Data Structures are kept and all other are removed. After this preprocessing, the selected feature vectors are used to train/test the forest.</p>
<p>The final step of preprocessing is to split the dataset into <b>trainDataset </b>and <b>testDataset</b>. The first 40 vectors are used for training, and the remaining 20 vectors are used for testing.</p>

<h3>1.2. Converting Scores/Grades into Labels</h3>
<p>The grades of the students are converted into the labels to use them for the training and testing of the forest. The labels for each grade is given in the following table:</p>

<table>
  <tr>
    <td><strong>Grade</strong></td>
    <td><strong>Label</strong></td>
  </tr>

  <tr>
    <td>A+, A, A-</td>
    <td>Excellent</td>
  </tr>

  <tr>
    <td>B+, B, B-</td>
    <td>Good</td>
  </tr>

  <tr>
    <td>C+, C, C-</td>
    <td>Average</td>
  </tr>

  <tr>
    <td>D+, D</td>
    <td>Bad</td>
  </tr>

  <tr>
    <td>FA, F</td>
    <td>Fail</td>
  </tr>

  <tr>
    <td>All others</td>
    <td>Unknown</td>
  </tr>
</table>
<p>Please note that the first alphabet of label is required to be capital.</p>

<h2>2. Model Training</h2>
<p>In this phase, the dataset is loaded into a linked list to create a forest of multiple decision-trees. The input to the forest are the following parameters:</p>
<ol>
<li>NumOfTrees: it represents the number of trees required in the forest</li>
<li>WindowSize: it represents the number of columns (features here) to use to split the root node of a decision-tree</li>
<li>StepSize: it is used to decide the first feature of the window of features for the root node (StepSize is used in combination with the WindowSize parameter)</li>
</ol>
<p>In order to make a tree different from the other, it uses a special technique of feature selection (as explained under). This technique is different from the well-known Random Forest algorithm, where the feature-set is selected randomly to create a root node of a decision-tree. In this simple technique, no randomness is involved.</p>

<h3>2.1. Creating a Single Decision-Tree</h3>
<p>Each decision-tree gives a set of rules to predict grades based on a single or combination of features. At each node of the tree, a feature is chosen that best splits the dataset. A best split divides the dataset into multiple partitions (linked-lists), each of them hosting observations that are more similar among themselves and different from the ones in the other partitions. Therefore, the importance of each feature is derived from how <b>&ldquo;pure&rdquo;</b> each of the partition is. The measure to calculate the impurity of a dataset is <b>Entropy </b>(and a respective <b>Information Gain</b>).</p>

<p>Following is a step-by-step process to build a decision-tree:</p>
<p><strong>Step 1: </strong>The forest passes <strong>WindowSize </strong>and <strong>FirstFeature </strong>to each decision-tree. For the first tree, the FirstFeature value is 0. For the next trees, it is calculated by adding the <em>StepSize </em>in the FirstFeature of the previous tree. Hence, the <em>FirstFeature </em>for the second tree would be 1*<em>StepSize </em>(and for the i<sup>th</sup> tree, it would be <em>(i-1)*StepSize</em>). The set of features comprising of the <em>FirstFeature </em>+ <em>WindowSize </em>is used in the root node of the tree to split the dataset.</p>
<p><strong>Step 2: </strong>If the <em>WindowSize </em>is 5 then the first 5 features are selected (indexed from 0 &ndash; 4) out of 16 features for the first tree. If the <em>StepSize </em>is 2 then the features 2 &ndash; 6 for the second tree are used, and so on.</p>
<p><strong>Step 3: </strong>The <em>entropy </em>of the entire dataset is calculated using the CS201 column (the last column). If the <em>entropy </em>is non-zero then the dataset is partitioned while increasing the purity of the partitioned subsets. In order to partition the dataset, calculate the <em>Entropy </em>and <em>Information Gain </em>of each feature that is selected in the step 2.</p>
<p><strong>Step 4: </strong>The feature with the highest <em>Information Gain </em>value is used to split the root node, and divide the dataset to its branches by grades value (each node can have 1 &ndash; 6 children, one for each grade label). Once the branches are created, the partitioned dataset is passed to the respective branch, i.e. for the branch with <em>Excellent </em>as its label, all the records having <em>Excellent </em>in the selected feature value goes to that branch.</p>
<p><strong>Step 5: </strong>For all the nodes below the root level, complete feature list to is used compete using <em>Information Gain </em>value. The feature with the highest <em>Information Gain </em>is used used to split that node.</p>
<p><strong>Step 6: </strong>A node with the entropy value equal to <em>zero </em>becomes a leaf node. Such a node contains the dataset where all the records have the same grade for the Data Structures course. When asked to predict, this leaf node returns this grade for the Data Structures course.</p>
<p><strong>Step 7: </strong>A branch with entropy more than 0 further splits using step 5. This process continues recursively on all the non-leaf nodes until all branches terminate on their respective leaf nodes.</p>

<h3>2.2. Creating a Forest</h3>
<p>Multiple decision-trees are generated, where each tree predicts the grade of data structures for a given input data. The forest collects the predictions from every decision-tree and return mode (majority voting) of the predictions as the final grade of data structures. If two or more grades appear to be the mode then all the modal grades will be the output predictions.</p>

<p>Same process of feature selection is repeated on each tree, trying to generate unique tree. The above mentioned technique does not guarantee that all trees are distinct, however, inorder to limit the duplicate trees to some extent the window is shifted by 2 in the round-robin fashion.</p>
<p>Example: Feature (s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) If the Windows_Size = 5 and No_of_trees = 5, then</p>
<p>Subset1 for root-selection of tree1 = {s1,s2,s3,s4,s5} and root node must be from these 5 features according to the value of the Gain.</p>
<p>Subset2 for root-selection of tree2 = {s3,s4,s5,s6,s7} and root node must be from these 5 features according to the value of the Gain.</p>
<p>Subset3 for root-selection of tree3 = {s5,s6,s7,s8,s9} and root node must be from these 5 features according to the value of the Gain.</p>
<p>Subset4 for root-selection of tree4 = {s7,s8,s9,s10,s1} and root node must be from these 5 features according to the value of the Gain.</p>
<p>Subset5 for root-selection of tree5 = {s9,s10,s1,s2,s3} and root node must be from these 5 features according to the value of the Gain.</p>

<h2>3. Modal Value Finding</h2>
<p>In order to predict the grade, the predictions from every decision-tree is collected and the mode (majority voting) of the predictions is the final grade of data structures. If there are more than one modal value then prediction is set of labels. If a tree does not find a branch for a given case, then it would return <em>Unknown </em>grade.</p>

<h2>4. Tree Traversals</h2>
<p>Following depth-first traversal methods are implemented in the project:</p>
<ol>
<li>In-order traversal</li>
<li>Pre-order traversal</li>
<li>Post-order traversal</li>
</ol>
<p>When a node is visited the feature number which split that node is printed.</p>

<h2>5. Model Testing (Prediction)</h2>
<p>The performance of machine learning model can't be evaluated on <b>trainDataset</b>. Therefore, <b>testDataset</b> is used for measuring accuracy. The predicted class labels returned from all the tress are used to calculate the prediction accuracy using the <a href="https://towardsdatascience.com/accuracy-precision-recall-or-f1-331fb37c5cb9">Formula</a>.</p>

<p><b>Note: </b>The code can be used for predicting other grades with changes in target class. The 6 labels can also be changed corresponding to the grades.</p>
