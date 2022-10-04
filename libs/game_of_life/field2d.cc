#include "field2d.h"

#include "common.h"

Field2D MakeField2D(const int rows, const int columns) {
  CHECK_GE(rows, 1);
  CHECK_GE(columns, 1);
  return Field2D(std::vector<std::vector<bool>>(rows, std::vector<bool>(columns)));
}

Field2D MakeField2D(std::vector<std::vector<bool>> field) {
  const int rows = field.size();
  CHECK_GE(rows, 1);
  const int columns = field[0].size();
  CHECK_GE(columns, 1);
  for (int i = 0; i < rows; ++i) {
    CHECK_EQ(static_cast<int>(field[i].size()), columns);
  }
  return Field2D(std::move(field));
}

bool Field2D::Get(const int row, const int column) const {
  return field_[row][column];
}

int Field2D::GetRows() const {
  return field_.size();
}

int Field2D::GetColumns() const {
  return field_[0].size();
}

bool Field2D::CanAdvance() const {
  const int rows = GetRows();
  const int columns = GetColumns();

  bool result = true;
  for (int column = 0; column + 2 < columns; ++column) {
    result &= !(field_[0][column] && field_[0][column + 1] && field_[0][column + 2]);
    result &= !(field_[rows - 1][column] && field_[rows - 1][column + 1] && field_[rows - 1][column + 2]);
  }

  for (int row = 0; row + 2 < rows; ++row) {
    result &= !(field_[row][0] && field_[row + 1][0] && field_[row + 2][0]);
    result &= !(field_[row][columns - 1] && field_[row + 1][columns - 1] && field_[row + 2][columns - 1]);
  }

  return result;
}

void Field2D::Advance() {
  std::fill(tmp1_.begin(), tmp1_.end(), false);
  const auto& row_prev = tmp1_;

  const int rows = GetRows();
  const int columns = GetColumns();

  for (int row = 0; row < rows; ++row) {
    std::swap(field_[row], tmp2_);
    const auto& row_cur = tmp2_;

    int alive_prev = 0;

    int alive_cur = 0;
    alive_cur += (row_prev[0] ? 1 : 0);
    alive_cur += (row_cur[0] ? 1 : 0);
    alive_cur += ((row + 1 < rows && field_[row + 1][0]) ? 1 : 0);

    int alive_next;
    for (int column = 0; column < columns; ++column) {
      alive_next = 0;
      if (column + 1 < columns) {
        alive_next += (row_prev[column + 1] ? 1 : 0);
        alive_next += (row_cur[column + 1] ? 1 : 0);
        alive_next += ((row + 1 < rows && field_[row + 1][column + 1]) ? 1 : 0);
      }

      const int alive = alive_prev + alive_cur + alive_next;
      if (row_cur[column] && (alive == 3 || alive == 4)) {
        field_[row][column] = true;
      } else if (!row_cur[column] && alive == 3) {
        field_[row][column] = true;
      } else {
        field_[row][column] = false;
      }

      std::swap(alive_prev, alive_cur);
      std::swap(alive_cur, alive_next);
    }

    std::swap(tmp1_, tmp2_);
  }
}

Field2D::Field2D(std::vector<std::vector<bool>> field)
    : field_(std::move(field)),
      tmp1_(field_[0].size()),
      tmp2_(field_[0].size()) {}

Field2D ParseField2D(const std::string& text) {
  std::vector<std::vector<bool>> field;
  int columns = -1;
  field.emplace_back();
  for (const char ch: text) {
    if (ch == '|') {
      if (columns == -1) {
        columns = field.back().size();
      }
      CHECK_EQ(columns, static_cast<int>(field.back().size()));
      field.emplace_back();
    } else if (ch == '0' || ch == '.') {
      field.back().push_back(false);
    } else if (ch == '1' || ch == '#') {
      field.back().push_back(true);
    }
  }

  if (columns == -1) {
    columns = field.back().size();
  }
  CHECK_EQ(columns, static_cast<int>(field.back().size()));
  return MakeField2D(std::move(field));
}

std::string SerializeField2D(const Field2D& field, const char alive, const char dead, const char separator) {
  std::string result;
  for (int row = 0; row < field.GetRows(); ++row) {
    for (int column = 0; column < field.GetColumns(); ++column) {
      result.push_back(field.Get(row, column) ? alive : dead);
    }
    if (row + 1 < field.GetRows()) {
      result.push_back(separator);
    }
  }
  return result;
}
