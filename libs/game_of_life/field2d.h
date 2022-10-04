#ifndef __GAME_OF_LIFE_FIELD_2D_H__
#define __GAME_OF_LIFE_FIELD_2D_H__

#include <string>
#include <vector>

class Field2D {
 public:
  // Constructors.
  friend Field2D MakeField2D(int rows, int columns);
  friend Field2D MakeField2D(std::vector<std::vector<bool>> field);

  bool Get(int row, int column) const;

  int GetRows() const;
  int GetColumns() const;

  // Returns true iff all the cells outside the field would remain dead on the
  // next iteration.
  bool CanAdvance() const;

  // Runs one step of the Game of Life assuming that the field is surrounded by
  // dead cells.
  void Advance();

 private:
  explicit Field2D(std::vector<std::vector<bool>> field);

  std::vector<std::vector<bool>> field_;
  std::vector<bool> tmp1_;
  std::vector<bool> tmp2_;
};

Field2D MakeField2D(int rows, int columns);
Field2D MakeField2D(std::vector<std::vector<bool>> field);

// Syntax:
//   |  row separator
//   .0 dead cell
//   #1 alive cell
//
// Examples:
//   ...|.#.|###    is a 3x3 field with 4 alive cells
//   0000|0100|1111 is a field with 3 rows, 4 columns and 5 alive cells
Field2D ParseField2D(const std::string& text);

std::string SerializeField2D(const Field2D& field, char alive = '#', char dead = '.', char separator = '|');

#endif /*__GAME_OF_LIFE_FIELD_2D_H__*/
