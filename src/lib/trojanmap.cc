#include "trojanmap.h"

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return
 * -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string &id) { 
   for(auto iter = data.begin(); iter != data.end(); iter++){
	  if(iter->first == id)   // iterate every item in data
	       {
	           return iter->second.lat;
	       }
	   }
  return -1;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist,
 * return -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string &id) {
  for(auto iter = data.begin(); iter != data.end(); iter++){
	  if(iter->first == id)   // iterate every item in data
	       {
	           return iter->second.lon;
	       }
	   }
  return -1;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return
 * "NULL".
 *
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string &id) {
  for(auto iter = data.begin(); iter != data.end(); iter++){
	  if(iter->first == id)   // iterate every item in data
	       {
	           return iter->second.name;
	       }
	   }
  return "NULL";
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return
 * an empty vector.
 *
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string &id) {
  for(auto iter = data.begin(); iter != data.end(); iter++){
	  if(iter->first == id)   // iterate every item in data
	       {
	           return iter->second.neighbors;
	       }
	   }
  return {};
}

/**
 * GetID: Given a location name, return the id.
 * If the node does not exist, return an empty string.
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(const std::string &name) {
  for(auto iter = data.begin(); iter != data.end(); iter++){
	  if(iter->second.name == name)   // iterate every item in data
	       {
	           return iter->first;
	       }
	   }
  std::string res = "";
  return res;
}

/**
 * GetPosition: Given a location name, return the position. If id does not
 * exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  for(auto iter = data.begin(); iter != data.end(); iter++){
	  if(iter->second.name == name)   // iterate every item in data
	       {
	          std::pair<double, double> 
            results(iter->second.lat, iter->second.lon);
            return results;
	       }
	   }
  std::pair<double, double> results(-1, -1);
  return results;
}

/**
 * CalculateEditDistance: Calculate edit distance between two location names
 *
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b) {   
  int n = a.length();
  int m = b.length();

  // empty case
  if (n * m == 0) return n + m;

  // DP array
  std::vector<std::vector<int>> D(n + 1, std::vector<int>(m + 1));

  // initialize boundary condition
  for (int i = 0; i < n + 1; i++) 
    D[i][0] = i;
  for (int j = 0; j < m + 1; j++) 
    D[0][j] = j;
  // calculate DP
  for (int i = 1; i < n + 1; i++) 
  {
    for (int j = 1; j < m + 1; j++) 
    {
      int left = D[i - 1][j] + 1;
      int down = D[i][j - 1] + 1;
      int left_down = D[i - 1][j - 1];
      if (a[i - 1] != b[j - 1]) 
        left_down += 1;
      D[i][j] = std::min(left, std::min(down, left_down));

    }
  }
        return D[n][m];
}

/**
 * FindClosestName: Given a location name, return the name with smallest edit
 * distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : similar name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  int min_distance = INT_MAX;
  // Node store;
  std::string temp_name; // changed
  if(name == temp_name)
  {
    return name;
  } // changed
  for(auto iter = data.begin(); iter != data.end(); iter++)
  {
	  int distance = CalculateEditDistance(iter->second.name, name);
    if(distance == 0)   // iterate every item in data
	  {
      // min_distance = 0;
      // store = iter->second;
      // return store.name;
      return  iter->second.name; // changed
	  }
    if(distance < min_distance)
    {
      min_distance = distance;
      temp_name = iter->second.name; // changed
      // store = iter->second;  
    }
	}
  return temp_name; // changed
  // return store.name;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name) {
  std::vector<std::string> results;
  if(name == "")
    return results;
  int size = name.size();
  for(int i = 0; i < size; i++)     //change name into pure lower case
  {
        if(name.at(i) >= 'A' && name.at(i) <= 'Z')
        {
            name.at(i) += 32;
        }
  }
  for(auto iter = data.begin(); iter != data.end(); iter++)
  {
    std::string temp_name = iter->second.name;
    if(size <= temp_name.size())
    {
        bool flag = true;
        for(int i = 0; i < size; i++)
        {
          // if(name.at(i) >= 'a' && name.at(i) <= 'z')
          // {
          //   if(name.at(i) == temp_name.at(i) || 
          //   name.at(i) - 32 == temp_name.at(i))
          //   {}
          //   else
          //     flag = false;
          // }
          // else
          // {
          //   if(name.at(i) != temp_name.at(i))
          //   flag = false;
          // }
          if((temp_name.at(i) >= 'A' && temp_name.at(i) <= 'Z') && (name.at(i) - 32 == temp_name.at(i))) // changed
          {
            continue;
          }
          else if(name.at(i) != temp_name.at(i))
          {
            flag = false;
            break;
          } // changed
        }
        if(flag == true)
          results.push_back(temp_name);
    }
	}
  return results;
}

/**
 * GetAllCategories: Return all the possible unique location categories, i.e.
 * there should be no duplicates in the output.
 *
 * @return {std::vector<std::string>}  : all unique location categories
 */
std::vector<std::string> TrojanMap::GetAllCategories() {
  std::set<std::string> ans;
  std::vector<std::string> ret;
  for(auto iter1 = data.begin(); iter1 != data.end(); iter1++)
  {
    if( iter1->second.attributes.size() == 0) // changed
    {
      continue;
    } // changed
    std::unordered_set<std::string> single = iter1->second.attributes;
    for(auto iter2 = single.begin(); iter2 != single.end(); iter2++)
    {
      ans.insert(*iter2);
    }
  }
  for(auto iter = ans.begin(); iter != ans.end(); iter++)
  {
    ret.push_back(*iter);
  }
  return ret;
}

/**
 * GetAllLocationsFromCategory: Return all the locations of the input category (i.e.
 * 'attributes' in data.csv). If there is no location of that category, return
 * (-1, -1). The function should be case-insensitive.
 *
 * @param  {std::string} category          : category name (attribute)
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetAllLocationsFromCategory(
    std::string category) {
  std::vector<std::string> res;
  for(int i = 0; i < category.length(); i++)
  {
    if(category.at(i) >= 'A' && category.at(i) <= 'Z')
    {
      category.at(i) += 32;
    }
  }
  for(auto iter = data.begin(); iter != data.end(); iter++)
  {
    if(iter->second.attributes.count(category))
    {
      res.push_back(iter->first);
    }
  }
  return res;
}

/**
 * GetLocationRegex: Given the regular expression of a location's name, your
 * program should first check whether the regular expression is valid, and if so
 * it returns all locations that match that regular expression.
 *
 * @param  {std::regex} location name      : the regular expression of location
 * names
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetLocationRegex(std::regex location) {
  std::vector<std::string> ret;
  for(auto iter = data.begin(); iter != data.end(); iter++)
  {
    // std::string temp = iter->second.name;
    // if(regex_match(temp, location))
    if(regex_match(iter->second.name, location)) // changed
    {
      ret.push_back(iter->first);
    }
  }
  return ret;
}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 *
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id,
                                    const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) *
                                           cos(b.lat * M_PI / 180.0) *
                                           pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(std::min(1.0, sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations
 * inside the vector.
 *
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0; i < int(path.size()) - 1; i++) {
    sum += CalculateDistance(path[i], path[i + 1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path
 * which is a list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> path;        //the return vector
  std::string id1 = GetID(location1_name);    //pick the ids
  std::string id2 = GetID(location2_name);

  //id, refreshed shortest distance, refreshed last position, visited or not
  // std::vector<std::string> ids; // changed
  // std::vector<double> distances; // changed
  // std::vector<std::string> last_position; // changed
  // std::vector<bool> visited; // changed

//use priority_queue for efficiency
//distance, id
  std::priority_queue< std::pair<double, std::string>, std::vector< std::pair<double, std::string> >, 
                        std::greater<std::pair<double, std::string> > > q;
//< id, < visited, <distance, last> > >
  std::unordered_map< std::string, std::pair< bool, std::pair<double, std::string> > > mark;
//insert the starting point
  q.push(std::pair<double, std::string>(0, id1));
  mark.insert(std::pair< std::string, std::pair< bool, std::pair<double, std::string> > >
              (id1, std::pair< bool, std::pair<double, std::string> >(false, std::pair<double, std::string>(0, "0"))));
  while(!q.empty())
  {
    // if(q.empty()) // changed
    //   break; // changed
    std::pair<double, std::string> current = q.top();
    if(current.second == id2)
      break;
    q.pop();
    mark[current.second].first = true;
    std::vector<std::string> current_neighbors = data[current.second].neighbors;
    for(auto i : current_neighbors)
    {
      double temp_distance = current.first + CalculateDistance(current.second, i);
      if(mark.find(i) == mark.end())
      {
        q.push(std::pair<double, std::string>(temp_distance, i));
        mark.insert(std::pair< std::string, std::pair< bool, std::pair<double, std::string> > >
              (i, std::pair< bool, std::pair<double, std::string> >(false, std::pair<double, std::string>(temp_distance, current.second))));
      }
      else if(mark[i].second.first > temp_distance)
      {
          mark[i].second.first = temp_distance;
          mark[i].second.second = current.second;
          q.push(std::pair<double, std::string>(temp_distance, i));
      }
    }
    while(!q.empty() && mark[q.top().second].first)       //remove unwanted tops
      q.pop();
  }
  if(q.empty())
    return path;
  std::string temp = q.top().second;
  while(temp != id1)
  {
    path.push_back(temp);
    temp = mark[temp].second.second;
  }
  path.push_back(temp);
  reverse(path.begin(), path.end());
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest
 * path which is a list of id. Hint: Do the early termination when there is no
 * change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name) {
  std::string id1 = GetID(location1_name);    //pick the ids
  std::string id2 = GetID(location2_name);
  //using the 1D method in the slides of lec 8
  std::unordered_map<std::string, double> distances;// map for refreshing distances
  std::unordered_map<std::string, std::string> lasts;//map for the last
  for(auto i : data)      //initialize the two maps
  {
    distances.insert(std::pair<std::string, double>(i.first, INT_MAX));
    lasts.insert(std::pair<std::string, std::string>(i.first, ""));
  }
  distances[id1] = 0;
  for (int i = 0; i < data.size() - 1; i++) 
  {
    bool flag = false;
    for (auto v : data) 
    {
      std::string cur = v.first;
      if(distances[cur]==INT_MAX) // changed
      {
        continue;
      } // changed
      for(auto neighbor : v.second.neighbors)
      {
        double newdistance = distances[cur] + CalculateDistance(neighbor, cur);
        if(distances[neighbor] > newdistance)
        {
          distances[neighbor] = newdistance;
          lasts[neighbor] = cur;
          flag = true;
        }
      }
    }
    if(!flag)     //if we didnt change anything in an epoch, we break
      break;
  }
  std::vector<std::string> path;    //get output
  path.push_back(id2);
  std::string temp = lasts[id2];
  while(temp != id1)
  {
    path.push_back(temp);
    temp = lasts[temp];
  }
  path.push_back(id1);
  reverse(path.begin(), path.end());

  return path;
}

/**
 * Traveling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::vector<std::vector<std::string>> recorded_path;
  std::unordered_map<std::string, bool> visited;
  double min_dis = INT_MAX;
  std::vector<std::string> min_path;
  double cur_dis = 0;
  std::vector<std::string> cur_path;
  for(std::string i : location_ids)
    visited.insert(std::pair<std::string, bool>(i, false));
  cur_path.push_back(*location_ids.begin());
  visited[*location_ids.begin()] = true;
  TravelingTrojan_Brute_force_helper(recorded_path, visited, min_dis, min_path, cur_dis, cur_path);
  records.first = min_dis;
  recorded_path.push_back(min_path);
  recorded_path.erase(recorded_path.begin());
  records.second = recorded_path;
  return records;
}

void TrojanMap::TravelingTrojan_Brute_force_helper(std::vector<std::vector<std::string>> &recorded_path, 
  std::unordered_map<std::string, bool> &visited, 
  double &min_dis, std::vector<std::string> &min_path, 
  double &cur_dis, std::vector<std::string> &cur_path){
    if(cur_path.size() == visited.size())
    {
      std::string tail = cur_path.back();
      std::string head = cur_path.front();
      cur_dis += CalculateDistance(tail, head);
      cur_path.push_back(head);
      if(cur_dis < min_dis)
      {
        recorded_path.push_back(min_path);
        min_dis = cur_dis;
        min_path = cur_path;
      }
      else
      {
        recorded_path.push_back(cur_path);
      }
      cur_dis -= CalculateDistance(tail, head);
      cur_path.pop_back();
      return;
    }
    for(std::unordered_map<std::string, bool>::iterator iter = visited.begin(); iter != visited.end(); iter++)
    {
      if(!iter->second)
      {
        std::string temp = cur_path.back();
        iter->second = true;
        cur_dis += CalculateDistance(temp, iter->first);
        cur_path.push_back(iter->first);
        TravelingTrojan_Brute_force_helper(recorded_path, visited, min_dis, min_path, cur_dis, cur_path);
        iter->second = false;
        cur_dis -= CalculateDistance(temp, iter->first);
        cur_path.pop_back();
      }
    }
    return;
  }

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::vector<std::vector<std::string>> recorded_path;
  std::unordered_map<std::string, bool> visited;
  double min_dis = INT_MAX;
  std::vector<std::string> min_path;
  double cur_dis = 0;
  std::vector<std::string> cur_path;
  for(std::string i : location_ids)
    visited.insert(std::pair<std::string, bool>(i, false));
  cur_path.push_back(*location_ids.begin());
  visited[*location_ids.begin()] = true;
  TravelingTrojan_Backtracking_helper(recorded_path, visited, min_dis, min_path, cur_dis, cur_path);
  records.first = min_dis;
  recorded_path.push_back(min_path);
  recorded_path.erase(recorded_path.begin());
  records.second = recorded_path;
  return records;
}

void TrojanMap::TravelingTrojan_Backtracking_helper(std::vector<std::vector<std::string>> &recorded_path, 
  std::unordered_map<std::string, bool> &visited, 
  double &min_dis, std::vector<std::string> &min_path, 
  double &cur_dis, std::vector<std::string> &cur_path){
    if(cur_dis > min_dis)       //the only difference to the original Brute force!
    {
      return;
    }
    if(cur_path.size() == visited.size())
    {
      std::string tail = cur_path.back();
      std::string head = cur_path.front();
      cur_dis += CalculateDistance(tail, head);
      cur_path.push_back(head);
      if(cur_dis < min_dis)
      {
        recorded_path.push_back(min_path);
        min_dis = cur_dis;
        min_path = cur_path;
      }
      else
      {
        recorded_path.push_back(cur_path);
      }
      cur_dis -= CalculateDistance(tail, head);
      cur_path.pop_back();
      return;
    }
    for(std::unordered_map<std::string, bool>::iterator iter = visited.begin(); iter != visited.end(); iter++)
    {
      if(!iter->second)
      {
        std::string temp = cur_path.back();
        iter->second = true;
        cur_dis += CalculateDistance(temp, iter->first);
        cur_path.push_back(iter->first);
        TravelingTrojan_Backtracking_helper(recorded_path, visited, min_dis, min_path, cur_dis, cur_path);
        iter->second = false;
        cur_dis -= CalculateDistance(temp, iter->first);
        cur_path.pop_back();
      }
    }
    return;
  }

// Hint: https://en.wikipedia.org/wiki/2-opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::vector<std::vector<std::string>> recorded_path;
  double best_distance;
  bool flag = true;
  location_ids.push_back(location_ids[0]);
  int size = location_ids.size();
  while(flag)
  {
    flag = false;
    best_distance = CalculatePathLength(location_ids);
    for(int i = 1; i < size-2; i++)
    {
      if(flag)
        break;
      for(int j = i + 1; j < size-1; j++)
      {
        std::vector<std::string> old_route = location_ids;
        reverse(location_ids.begin() + i, location_ids.begin() + j + 1);
        double new_distance = CalculatePathLength(location_ids);
        recorded_path.push_back(location_ids);
        if(new_distance < best_distance)
        {
          best_distance = new_distance;
          flag = true;
          break;
        }
        else
          location_ids = old_route;
        
      }
    }
  }
  records.first = CalculatePathLength(location_ids);
  recorded_path.push_back(location_ids);
  records.second = recorded_path;
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(
    std::string locations_filename) {
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, word)) {
    location_names_from_csv.push_back(word);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(
    std::string dependencies_filename) {
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    std::vector<std::string> dependency;
    while (getline(s, word, ',')) {
      dependency.push_back(word);
    }
    dependencies_from_csv.push_back(dependency);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a
 * sorting of nodes that satisfies the given dependencies. If there is no way to
 * do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     :
 * prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(
    std::vector<std::string> &locations,
    std::vector<std::vector<std::string>> &dependencies) {
  std::vector<std::string> result;
  while(result.size() < locations.size())
  {
    int original_size = result.size();
    for(auto node : locations)
    {
      bool flag = true;
      for(auto direction : dependencies)
      {
        //find the node(s) that cannot be approached by other nodes
        if(direction[1] == node && !std::count(result.begin(), result.end(), direction[0]))
        {
          flag = false;
          break;
        }
      }
      if(flag && !std::count(result.begin(), result.end(), node))
        result.push_back(node);
    }
    if(original_size == result.size())    //size not changing in an epoch means no such node
    {
      result.clear();
      return result;
    }
  }
  
  return result;     
}

/**
 * inSquare: Give a id return whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
  //left, right, upper, lower
  double lon = GetLon(id);
  double lat = GetLat(id);
  if(lon > square[0] && lon < square[1] && lat < square[2] && lat > square[3])
    return true;
  return false;
}

/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location
 * ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square
 * area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the
 * square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  for(auto i : data)
  {
    if(inSquare(i.first, square))
      subgraph.push_back(i.first);
  }
  return subgraph;
}

/**
 * Cycle Detection helper
 *
 */
bool TrojanMap::CycleDetectionhelper(std::string root, std::map<std::string, bool> &visited, 
                                      std::string prev, std::vector<std::string>  &cycle) {
  for(auto i : data[root].neighbors)
  {
    if(visited.find(i) != visited.end())    // the node is in the square
    {
      if(i != prev)                         //not the prev node
      {
        if(visited[i])                      //it has been visited
        { // changed
          cycle.push_back(i); // changed
          return true;
        }   // changed
        else
        {
          visited[i] = true;
          cycle.push_back(i);
          bool temp = CycleDetectionhelper(i, visited, root, cycle);
          if(temp == true)
            return true;
          cycle.pop_back();
        }
      }
    }
  }
  return false;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true
 * if there is a cycle path inside the square, false otherwise.
 *
 * @param {std::vector<std::string>} subgraph: list of location ids in the
 * square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {std::vector<std::string>}: the cycle, empty vector if it doesnot exist
 */
bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, 
                              std::vector<double> &square) {
  std::map<std::string, bool> visited;
  for(auto i : subgraph)
    visited.insert(std::pair<std::string, bool>(i, false));
  std::string root = subgraph[0];
  std::string prev = "";
  visited[root] = true;
  bool flag = false;
  bool ans = false;
  subgraph.clear();
  while(!flag)
  {
    subgraph.push_back(root);
    ans = CycleDetectionhelper(root, visited, prev, subgraph);
    if(ans)
    {
      return true;
    }
    subgraph.pop_back();
    flag = true;              //assume all the bools in visited is true, if we find a false, set flag false
    for(auto temp : visited)
    {
      if(!temp.second)
      {
        root = temp.first;
        prev = "";
        visited[root] = true;
        flag = false;
        break;
      }
    }
  }
  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r,
 * find all locations in class C on the map near L with the range of r and
 * return a vector of string ids
 *
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {int} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, 
                                              std::string name, double r, int k) {
  //category, center, radius, max number
  std::string center_id;    //id of the center
  std::vector<std::pair<double, std::string>> selected;   //pair<distance, location id>
  for(auto i : data)    //find the center id
  {
    if(i.second.name == name)
      center_id = i.first;
  }
  for(auto i : data)
  {
    bool flag = false;
    for(auto j : i.second.attributes)   //get the items belong to the attribute
    {
      if(j == attributesName)
      {
        flag = true;
        break;
      }
    }
    if(flag)  //the node have such a category
    {
      double distance = CalculateDistance(center_id, i.first);
      if(distance != 0 && distance < r) //not the center, in the circle
        selected.push_back(std::pair<double, std::string>(distance, i.first));
    }
  }
  std::sort(selected.begin(), selected.end());
  std::vector<std::string> res;
  for(int i = 0; i < k; i++)
  {
    if(selected.begin() + i != selected.end())  //in case the found ones are short in number than the objected number
    {
      res.push_back((selected.begin() + i)->second);
    }
    else
      break;
  }
  return res;
}

/**
 * Shortest Path to Visit All Nodes: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of
 * total distance and the all the progress to get final path
 */
std::vector<std::string> TrojanMap::TrojanPath(
      std::vector<std::string> &location_names) {
    std::vector<std::string> location_ids;    //get the ids
    for(auto i : location_names)
    {
      for(auto j : data)
      {
        if(j.second.name == i)
          location_ids.push_back(j.first);
      }
    }
    std::pair<double, std::vector<std::vector<std::string>>> min;
    min.first = INT_MAX;
    std::pair<double, std::vector<std::vector<std::string>>> cur;
    cur.first = 0;
    std::unordered_map<std::string, bool> visited;
    for(std::string i : location_ids)
      visited.insert(std::pair<std::string, bool>(i, false));
    for(std::string i : location_ids)         //start from different points
    {
      visited[i] = true;
      TrojanPath_helper(i, min, cur, visited);
      visited[i] = false;
    }

    //put the result in the vector
    std::vector<std::string> res;
    for(int i = 0; i < min.second.size(); i++)
    {
      for(int j = 0; j < min.second[i].size(); j++)
      {
        if(j == 0 && i != 0)
          continue;
        res.push_back(min.second[i][j]);
      }
    }
    return res;
}

//***********************************************************************************************
  void TrojanMap::TrojanPath_helper(std::string prev, std::pair<double, std::vector<std::vector<std::string>>> &min, 
  std::pair<double, std::vector<std::vector<std::string>>> &cur, std::unordered_map<std::string, bool> &visited){
    if(cur.first > min.first)         //backtracking
      return;
    if(cur.second.size() == visited.size() - 1)     //refreshing the min
    {
      if(cur.first < min.first)
        min = cur;
      return;
    }
    for(std::unordered_map<std::string, bool>::iterator iter = visited.begin(); iter != visited.end(); iter++)
    {
      if(!iter->second)
      {       
        std::vector<std::string> cur_path =  CalculateShortestPath_Dijkstra(data[prev].name, data[iter->first].name);
        double cur_length = CalculatePathLength(cur_path);
        iter->second = true;
        cur.first += cur_length;
        cur.second.push_back(cur_path);
        TrojanPath_helper(iter->first, min, cur, visited);      //control the conditions
        iter->second = false;
        cur.first -= cur_length;
        cur.second.pop_back();
      }
    }
    return;
  }
//***********************************************************************************************

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 *
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0])) n.attributes.insert(word);
        if (isdigit(word[0])) n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}
