#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(TrojanMapStudentTest, Autocomplete_001) {
  TrojanMap m;
  // Test the simple case
  auto names = m.Autocomplete("St");
  std::unordered_set<std::string> gt =                // groundtruth for "Ch"
  {"Starbucks","Student Union (STU)","St. Francis Center - Food Bank",
  "Starbucks 2","Starbucks 1","Stimson House","Strangers Rest Baptist Church",
  "St Agnes Church","St. Johns Cathedral-Hope Net","St. Philips Episcopal Church",
  "Starbucks 3","Stout Burger","Studio 423"}; 
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the lower case
  names = m.Autocomplete("st");
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the lower and upper case 
  names = m.Autocomplete("sT"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the upper case 
  names = m.Autocomplete("ST"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
}

TEST(TrojanMapStudentTest, FindPosition_001) {
  TrojanMap m;

  // Test Starbucks
  auto position = m.GetPosition("Starbucks");
  std::pair<double, double> gt1(34.0390615, -118.2611170); // groundtruth for "Starbucks"
  EXPECT_EQ(position, gt1);

  // Test Ross
  position = m.GetPosition("Ross");
  std::pair<double, double> gt2(34.0044118, -118.2821764); // groundtruth for "Ross"
  EXPECT_EQ(position, gt2);
  
  //Test Unknown
  position = m.GetPosition("qwerty");
  std::pair<double, double> gt3(-1, -1);
  EXPECT_EQ(position, gt3);
}

TEST(TrojanMapStudentTest, CalculateEditDistance_001) {
  TrojanMap m;
  EXPECT_EQ(m.CalculateEditDistance("horse", "ros"), 3);
  EXPECT_EQ(m.CalculateEditDistance("intention", "execution"), 5);
  EXPECT_EQ(m.CalculateEditDistance("zoologicoarchaeologist", "zoogeologist"), 10);
}

TEST(TrojanMapStudentTest, FindClosestName_001) {
  TrojanMap m;
  EXPECT_EQ(m.FindClosestName("Rolphs"), "Ralphs");
  EXPECT_EQ(m.FindClosestName("Targeety"), "Target");
  EXPECT_EQ(m.FindClosestName("storebuc"), "Starbucks");
}

TEST(TrojanMapStudentTest, GetAllCategories_001) {
  TrojanMap m;

  auto categories = m.GetAllCategories();
  std::vector<std::string> gt{
      "artwork","attraction","bakery","bank","bar","beauty","beverages",
      "bicycle","bicycle_rental","bus_station","cafe","car","car_repair","car_wash",
      "charging_station","childcare","clinic","clothes","confectionery","convenience","copyshop",
      "dentist","department_store","driving_school","fabric","fast_food","food_court","fountain",
      "fuel","gallery","hairdresser","hospital","hotel","library","marketplace",
      "mobile_phone","museum","music","optician","parcel_locker","parking","parking_entrance",
      "pharmacy","place_of_worship","police","post_box","post_office","restaurant","school",
      "shoe_repair","shoes","skate","social_facility","supermarket","theatre","tobacco",
      "yes","yoga"}; // Expected Categories
  EXPECT_EQ(categories, gt);
}

TEST(TrojanMapStudentTest, GetAllLocationsFromCategory_001) {
  TrojanMap m;

  auto ids1 = m.GetAllLocationsFromCategory("LiBrary");
  auto ids2 = m.GetAllLocationsFromCategory("BEAUTY");
  auto ids3 = m.GetAllLocationsFromCategory("music");
  std::vector<std::string> gt1{
      "6042978413","368169838","368169848","368169842","3699294513"}; // Expected ids
  std::vector<std::string> gt2{
      "9591449459","6047204780"}; // Expected ids
  std::vector<std::string> gt3{
      "5695183055","5695174693"}; // Expected ids
  EXPECT_EQ(ids1, gt1);
  EXPECT_EQ(ids2, gt2);
  EXPECT_EQ(ids3, gt3);
}

TEST(TrojanMapStudentTest, GetLocationRegex_001) {
  TrojanMap m;

  std::regex input1("Ralphs");
  auto ids1 = m.GetLocationRegex(input1);
  std::vector<std::string> gt1{
      "2578244375"}; // Expected ids
  EXPECT_EQ(ids1, gt1);

  std::regex input2("(Hill)(.*)");
  auto ids2 = m.GetLocationRegex(input2);
  std::vector<std::string> gt2
  {"9596557992","9587039895","6279600804","9587039894","6279600805","6279600812","6123510350","4291108051",
  "6123510349","6279600806","6279600807","6279600808","6279600811","6503044368","9598720154"}; // Expected ids
  EXPECT_EQ(ids2, gt2);

  std::regex input3("abcde");
  auto ids3 = m.GetLocationRegex(input3);
  std::vector<std::string> gt3 = {}; // Expected ids
  EXPECT_EQ(ids3, gt3);
}

TEST(TrojanMapStudentTest, CalculateShortestPath_Dijkstra_001) {
  TrojanMap m;
  
  // Test from Ralphs to Porterhouse Fried Chicken
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Porterhouse Fried Chicken");
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920",
      "6818427919","6818427918","6818427892","6818427898","6818427917","6818427916",
      "7232024780","6813416145","6813416154","6813416153","6813416152","6813416151",
      "6813416155","6808069740","6816193785","6816193786","123152294","4015203136",
      "4015203134","4015203133","6813405212","6813405215","6813405216","6813405217",
      "6813405218","6813405219","6813405220","6816193787","6814958435","4583263530",
      "1473199412","123660671","2613081563","122827893","6817053930","6805827732",
      "122827894","1771091141","6805054066","1878026177","4015203119","4015203118",
      "6814958406","123209605","6814958408","5567718503","5567736373","7229539444",
      "1771091142","123019475","123019477","122625127","122625129","4009744690",
      "211752888","601390387","2193439965","123112737","1615672692","123289577",
      "2613073695","122688464","2613073691","2613073722","122670308","2613073700",
      "122670310","1732243947","5249489005","2613073701","2613073699","1732243600",
      "2613073711","2613073706","8381644786","1732243497","4010228233","4059536885",
      "5572759107","6278441428","5572759108","6278441401","6278441406","6278441405",
      "6278441404","6278441403","6278441420","5572759111","6278441398","1846353192",
      "6276831466","2613066293","7811377079","7811377078","7811377077","7812139745",
      "7812139746","6276831456","8810486870","6276832387","6276832386","6276832385",
      "6276831484","6276831483","122991354","2613066288","122991356","122736901",
      "2613066332","2613066324","122728843","2613066321","122728845","2613066284",
      "122728847","2613066315","122728849","4010228203","1474987714","4630579203"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Porterhouse Fried Chicken to Ralphs
  path = m.CalculateShortestPath_Dijkstra("Porterhouse Fried Chicken", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapStudentTest, CalculateShortestPath_Dijkstra_002) {
  TrojanMap m;
  
  // Test from Ralphs to Target
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Target");
  std::vector<std::string> gt{
        "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469",
        "6813416131","7645318201","6813416130","6813416129","123318563","452688940",
        "6816193777","123408705","6816193774","452688933","452688931","123230412",
        "6816193770","6787470576","4015442011","6816193692","6816193693","6816193694",
        "4015377691","544693739","6816193696","6804883323","6807937309","6807937306",
        "6816193698","4015377690","4015377689","122814447","6813416159","6813405266",
        "4015372488","4015372487","6813405229","122719216","6813405232","4015372486",
        "7071032399","4015372485","6813379479","6813379584","6814769289","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Target to Ralphs
  path = m.CalculateShortestPath_Dijkstra("Target", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapStudentTest, CalculateShortestPath_Dijkstra_003) {
  TrojanMap m;
  
  // Test from Starbucks 2 to Target
  auto path = m.CalculateShortestPath_Dijkstra("Starbucks 2", "Target");
  std::vector<std::string> gt{
        "4399693642","6808200836","6808200835","6808200834","6808200837","6808200833",
        "4091160832","4091160831","4091160830","4091160823","3402887079","6818390141",
        "6818390142","6818390139","6818390143","6045054380","6813379418","6047234443",
        "6813379419","9591449515","6814820015","6814820010","6814820018","6814769290",
        "9591449485","6396649383","6814769289","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Target to Starbucks 2
  path = m.CalculateShortestPath_Dijkstra("Target", "Starbucks 2");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford_001) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Porterhouse Fried Chicken");
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920",
      "6818427919","6818427918","6818427892","6818427898","6818427917","6818427916",
      "7232024780","6813416145","6813416154","6813416153","6813416152","6813416151",
      "6813416155","6808069740","6816193785","6816193786","123152294","4015203136",
      "4015203134","4015203133","6813405212","6813405215","6813405216","6813405217",
      "6813405218","6813405219","6813405220","6816193787","6814958435","4583263530",
      "1473199412","123660671","2613081563","122827893","6817053930","6805827732",
      "122827894","1771091141","6805054066","1878026177","4015203119","4015203118",
      "6814958406","123209605","6814958408","5567718503","5567736373","7229539444",
      "1771091142","123019475","123019477","122625127","122625129","4009744690",
      "211752888","601390387","2193439965","123112737","1615672692","123289577",
      "2613073695","122688464","2613073691","2613073722","122670308","2613073700",
      "122670310","1732243947","5249489005","2613073701","2613073699","1732243600",
      "2613073711","2613073706","8381644786","1732243497","4010228233","4059536885",
      "5572759107","6278441428","5572759108","6278441401","6278441406","6278441405",
      "6278441404","6278441403","6278441420","5572759111","6278441398","1846353192",
      "6276831466","2613066293","7811377079","7811377078","7811377077","7812139745",
      "7812139746","6276831456","8810486870","6276832387","6276832386","6276832385",
      "6276831484","6276831483","122991354","2613066288","122991356","122736901",
      "2613066332","2613066324","122728843","2613066321","122728845","2613066284",
      "122728847","2613066315","122728849","4010228203","1474987714","4630579203"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Bellman_Ford("Porterhouse Fried Chicken", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapStudentTest, CalculateShortestPath_Bellman_Ford_002) {
  TrojanMap m;
  
  // Test from Ralphs to Target
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Target");
  std::vector<std::string> gt{
        "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469",
        "6813416131","7645318201","6813416130","6813416129","123318563","452688940",
        "6816193777","123408705","6816193774","452688933","452688931","123230412",
        "6816193770","6787470576","4015442011","6816193692","6816193693","6816193694",
        "4015377691","544693739","6816193696","6804883323","6807937309","6807937306",
        "6816193698","4015377690","4015377689","122814447","6813416159","6813405266",
        "4015372488","4015372487","6813405229","122719216","6813405232","4015372486",
        "7071032399","4015372485","6813379479","6813379584","6814769289","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Target to Ralphs
  path = m.CalculateShortestPath_Bellman_Ford("Target", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapStudentTest, CalculateShortestPath_Bellman_Ford_003) {
  TrojanMap m;
  
  // Test from Starbucks 2 to Target
  auto path = m.CalculateShortestPath_Bellman_Ford("Starbucks 2", "Target");
  std::vector<std::string> gt{
        "4399693642","6808200836","6808200835","6808200834","6808200837","6808200833",
        "4091160832","4091160831","4091160830","4091160823","3402887079","6818390141",
        "6818390142","6818390139","6818390143","6045054380","6813379418","6047234443",
        "6813379419","9591449515","6814820015","6814820010","6814820018","6814769290",
        "9591449485","6396649383","6814769289","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Target to Starbucks 2
  path = m.CalculateShortestPath_Bellman_Ford("Target", "Starbucks 2");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, CycleDetection_001) {
  TrojanMap m;
  
  // Test case 1
  std::vector<double> square1 = {-118.270, -118.260, 34.030, 34.010};
  auto sub1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(sub1, square1);
  EXPECT_EQ(result1, true);

  // Test case 2
  std::vector<double> square2 = {-118.260, -118.259, 34.039, 34.037};
  auto sub2 = m.GetSubgraph(square2);
  bool result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, false);

  // Test case 3
  std::vector<double> square3 = {-118.311, -118.310, 34.011, 34.010};
  auto sub3 = m.GetSubgraph(square3);
  bool result3 = m.CycleDetection(sub3, square3);
  EXPECT_EQ(result3, false);
}

TEST(TrojanMapTest, TopologicalSort_001) {
  TrojanMap m;

  std::vector<std::string> location_names1 = {"Ralphs", "New Orleans Fish Market", "Saint James Park", "Arco","Expo Park/USC"};
  std::vector<std::vector<std::string>> dependencies1 = 
  {{"Ralphs","Saint James Park"}, {"Ralphs","Arco"}, {"New Orleans Fish Market","Saint James Park"}, {"Arco","New Orleans Fish Market"},{"Arco","Expo Park/USC"},{"Expo Park/USC","New Orleans Fish Market"}};
  auto result1 = m.DeliveringTrojan(location_names1, dependencies1);
  std::vector<std::string> gt1 ={"Ralphs", "Arco","Expo Park/USC","New Orleans Fish Market", "Saint James Park"};
  EXPECT_EQ(result1, gt1);

  std::vector<std::string> location_names2 = 
  {"Expo/Vermont 1", "Electric Vehicle Charging Station", "Kedren Community Health Center", "The Sonshine Shop Thrift Store",
  "Lee's Market","Dornsife Spatial Sciences Institute","CVS Pharmacy","7-Eleven"};
  std::vector<std::vector<std::string>> dependencies2 = 
  {{"Expo/Vermont 1","Electric Vehicle Charging Station"}, {"Electric Vehicle Charging Station","Kedren Community Health Center"}, 
  {"Kedren Community Health Center","The Sonshine Shop Thrift Store"},{"The Sonshine Shop Thrift Store","Lee's Market"},
  {"Lee's Market","Dornsife Spatial Sciences Institute"},{"Dornsife Spatial Sciences Institute","CVS Pharmacy"},{"CVS Pharmacy","7-Eleven"}};
  auto result2 = m.DeliveringTrojan(location_names2, dependencies2);
  std::vector<std::string> gt2 =
  {"Expo/Vermont 1", "Electric Vehicle Charging Station", "Kedren Community Health Center", "The Sonshine Shop Thrift Store",
  "Lee's Market","Dornsife Spatial Sciences Institute","CVS Pharmacy","7-Eleven"};
  EXPECT_EQ(result2, gt2);

  std::vector<std::string> location_names3 = {"Ralphs", "Chick-fil-A", "KFC"};
  std::vector<std::vector<std::string>> dependencies3 = 
  {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, {"Chick-fil-A", "KFC"}};
  auto result3 = m.DeliveringTrojan(location_names3, dependencies3);
  std::vector<std::string> gt3 ={"Ralphs", "Chick-fil-A", "KFC"};
  EXPECT_EQ(result3, gt3);
}

TEST(TrojanMapStudentTest, TSP1_001) {
  TrojanMap m;
  
  std::vector<std::string> input{"7863628174","7223875618","250745146"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"7863628174","250745146","7223875618","7863628174"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  // for(auto t : result.second)
  // {
  //   for(auto x : t)
  //   {
  //     std::cout << x << std::endl; 
  //   }
  //   std::cout<< "***************" <<std::endl;
  // }
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TSP1_002) {
  TrojanMap m;
  
  std::vector<std::string> input{"4009673255","6805498574","2514542194","2613066315","2611809729"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"4009673255","2514542194","2613066315","6805498574","2611809729","4009673255"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  // for(auto t : result.second)
  // {
  //   for(auto x : t)
  //   {
  //     std::cout << x << std::endl; 
  //   }
  //   std::cout<< "***************" <<std::endl;
  // }
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TSP1_003) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  // for(auto t : result.second)
  // {
  //   for(auto x : t)
  //   {
  //     std::cout << x << std::endl; 
  //   }
  //   std::cout<< "***************" <<std::endl;
  // }
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TSP2_001) {
  TrojanMap m;
  
  std::vector<std::string> input{"7863628174","7223875618","250745146"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"7863628174","250745146","7223875618","7863628174"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  // for(auto t : result.second)
  // {
  //   for(auto x : t)
  //   {
  //     std::cout << x << std::endl; 
  //   }
  //   std::cout<< "***************" <<std::endl;
  // }
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TSP2_002) {
  TrojanMap m;
  
  std::vector<std::string> input{"4009673255","6805498574","2514542194","2613066315","2611809729"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"4009673255","2514542194","2613066315","6805498574","2611809729","4009673255"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  // for(auto t : result.second)
  // {
  //   for(auto x : t)
  //   {
  //     std::cout << x << std::endl; 
  //   }
  //   std::cout<< "***************" <<std::endl;
  // }
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TSP2_003) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  // for(auto t : result.second)
  // {
  //   for(auto x : t)
  //   {
  //     std::cout << x << std::endl; 
  //   }
  //   std::cout<< "***************" <<std::endl;
  // }
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TSP3_001) {
  TrojanMap m;
  
  std::vector<std::string> input{"7863628174","7223875618","250745146"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"7863628174","250745146","7223875618","7863628174"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  // for(auto t : result.second)
  // {
  //   for(auto x : t)
  //   {
  //     std::cout << x << std::endl; 
  //   }
  //   std::cout<< "***************" <<std::endl;
  // }
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TSP3_002) {
  TrojanMap m;
  
  std::vector<std::string> input{"4009673255","6805498574","2514542194","2613066315","2611809729"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"4009673255","2514542194","2613066315","6805498574","2611809729","4009673255"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  // for(auto t : result.second)
  // {
  //   for(auto x : t)
  //   {
  //     std::cout << x << std::endl; 
  //   }
  //   std::cout<< "***************" <<std::endl;
  // }
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TSP3_003) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  // for(auto t : result.second)
  // {
  //   for(auto x : t)
  //   {
  //     std::cout << x << std::endl; 
  //   }
  //   std::cout<< "***************" <<std::endl;
  // }
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, FindNearby_001) {
  TrojanMap m;
  
  auto result = m.FindNearby("supermarket", "Ralphs", 10, 10);
  std::vector<std::string> ans{"5237417649", "6045067406", "7158034317"};
  EXPECT_EQ(result, ans);
}

TEST(TrojanMapStudentTest, FindNearby_002) {
  TrojanMap m;
  
  auto result = m.FindNearby("bank", "KFC", 10, 10);
  std::vector<std::string> ans{"9591449441", "5237417651", "9591449465"};
  EXPECT_EQ(result, ans);
}

TEST(TrojanMapStudentTest, FindNearby_003) {
  TrojanMap m;
  
  auto result = m.FindNearby("fast_food", "Leavey Library", 5, 5);
  std::vector<std::string> ans{"9591449455", "5567733799", "4577908517", "5567724155", "732641023"};
  EXPECT_EQ(result, ans);
}



TEST(TrojanMapStudentTest, CalculateShortestPath_TrojanPath_001) {
  TrojanMap m;
  
  // Test for Ralphs, KFC and Chick-fil-A 
  std::vector<std::string> input = {"KFC", "Ralphs", "Chick-fil-A"};
  auto path = m.TrojanPath(input);
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469","6813416131",
      "7645318201","6813416130","6813416129","123318563","452688940","6816193777","123408705",
      "6816193774","452688933","452688931","123230412","6816193770","6787470576","4015442011",
      "6816193692","6816193693","6816193694","3398621886","3398621887","6816193695","5690152756",
      "6804883324","3398621888","6813416123","6813416171","6807536647","6807320427","6807536642",
      "6813416166","7882624618","7200139036","122814440","6813416163","7477947679","7298150111",
      "6787803640","6807554573","2613117890","4835551096","4835551101","4835551097","4835551100",
      "3088547686","4835551100","4835551099","4835551098","6813565307","6813565306","6813565305",
      "6813565295","6813565296","3402814832","4835551107","6813379403","6813379533","3402814831",
      "6813379501","3402810298","6813565327","3398574883","6813379494","6813379495","6813379544",
      "6813379545","6813379536","6813379546","6813379547","6814916522","6814916523","1732243620",
      "4015372469","4015372463","6819179749","1732243544","6813405275","348121996","348121864",
      "6813405280","1472141024","6813411590","216155217","6813411589","1837212103","1837212101",
      "6814916516","6814916515","6820935910","4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  input = {"Ralphs", "Chick-fil-A", "KFC"};
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);

  input = {"Ralphs", "KFC", "Chick-fil-A"};
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);

}

TEST(TrojanMapStudentTest, CalculateShortestPath_TrojanPath_002) {
  TrojanMap m;
  
  // Test for Ralphs, KFC and Chick-fil-A 
  std::vector<std::string> input = {"Starbucks 2", "Ralphs", "Chase"};
  auto path = m.TrojanPath(input);
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920",
      "6818427919","6818427918","6818427892","6818427898","6818427917","6818427916",
      "7232024780","6813416145","6813416154","6813416153","6813416152","6813416151",
      "6813416155","6808069740","6816193785","6816193786","123152294","4015203136",
      "4015203134","4015203133","21098539","1286136440","6352860083","6808200832",
      "6808200833","6808200837","6808200834","6808200835","6808200836","4399693642",
      "6808200836","6808200835","6808200834","6808200837","6808200833","4091160832",
      "4091160831","4091160830","4091160823","3402887079","6818390141","6818390142",
      "1286136450","6818390138","6813379472","6804866264","6804866255","5690152765",
      "6813379478","4015423965","6807479782","6813379442","6813379468","6813379465",
      "6813379469","2783295153","6813379408","9591449452","6807200381","6813379456",
      "6818390146","3872400990","3402917921","3402917919","9559739236","6045067409",
      "3398574883","9559739232","9591449441"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  input = {"Ralphs", "Starbucks 2", "Chase"};
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);

  input = {"Ralphs", "Chase", "Starbucks 2"};
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);

}

TEST(TrojanMapStudentTest, CalculateShortestPath_TrojanPath_003) {
  TrojanMap m;
  
  // Test for Ralphs, KFC and Chick-fil-A 
  std::vector<std::string> input = {"Starbucks 2", "Ralphs", "Target", "Holbox"};
  auto path = m.TrojanPath(input);
  std::vector<std::string> gt1{
      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920",
      "6818427919","6818427918","6818427892","6818427898","6818427917","6818427916",
      "7232024780","6813416145","6813416154","6813416153","6813416152","6813416151",
      "6813416155","6808069740","6816193785","6816193786","123152294","4015203136",
      "4015203134","4015203133","21098539","1286136440","6352860083","6808200832",
      "6808200833","6808200837","6808200834","6808200835","6808200836","4399693642",
      "6808200836","6808200835","6808200834","6808200837","6808200833","4091160832",
      "4091160831","4091160830","4091160823","3402887079","6818390141","6818390142",
      "6818390139","6818390143","6045054380","6813379418","6047234443","6813379419",
      "9591449515","6814820015","6814820010","6814820018","6814769290","9591449485",
      "6396649383","6814769289","5237417650","6814769289","6813379584","6813360961",
      "6813379480","6813360960","6814620882","6813360954","6813360952","6813379420",
      "6813360951","6813360936","6813379467","6813379466","21306060","6813379469",
      "6813379427","123005255","6807200376","6807200380","6813379451","6813379463",
      "123327639","6813379460","4141790922","4015423963","9559739235","1286136447",
      "1286136422","4015423962","6813379494","63068643","6813379493","4015423961",
      "4015423960","7860380185","4015423959","9591448314","1841835270","2193435032",
      "1378231753","9591449436","123292100","123292045","4012759747","4012759746",
      "123280934","441893821","544348508","6815182444","7211629027","4872886234",
      "4872886233","4872886231","6655857589"}; // Expected path
  // Print the path lengths
  std::vector<std::string> gt2 = gt1;
  reverse(gt1.begin(), gt1.end());
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt1) << "miles" << std::endl;
  bool flag = false;
  if(path == gt1 || path == gt2)
    flag = true;
  EXPECT_EQ(flag, true);

  input = {"Target", "Starbucks 2", "Ralphs", "Holbox"};
  path = m.TrojanPath(input);

  flag = false;
  if(path == gt1 || path == gt2)
    flag = true;
  EXPECT_EQ(flag, true);

  input = {"Ralphs", "Target", "Holbox", "Starbucks 2"};
  path = m.TrojanPath(input);
  
  flag = false;
  if(path == gt1 || path == gt2)
    flag = true;
  EXPECT_EQ(flag, true);
}