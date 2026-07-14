#ifndef _UTIL_TRIGGER__H_
#define _UTIL_TRIGGER__H_

namespace UtilTrigger {
  int  Hodo2Road(const int h1, const int h2, const int h3, const int h4, const int tb);
  void Road2Hodo(const int road, int& h1, int& h2, int& h3, int& h4, int& tb);
  int FlipRoadLeftRight(const int road);
  int FlipRoadTopBottom(const int road);

  std::vector<int> ReadRoadList(const std::string fname);
  std::vector<int> ReadRoadList(const int rs_id, const int plus_minus, const int top_bottom);
  std::vector<int> FindEnabledRoads(const std::vector<int>& list_road_id, const std::vector<int>& roadset);
  bool IsEnabledRoad(const int road_id, const std::vector<int>& roadset);
}; // namespace UtilTrigger

#endif // _UTIL_TRIGGER__H_
