#ifndef ChessPlusPlusBoardConfigurationManagerClass_HeaderPlusPlus
#define ChessPlusPlusBoardConfigurationManagerClass_HeaderPlusPlus

#include "Configuration.hpp"

#include <string>
#include <fstream>
#include <streambuf>
#include <cstdint>
#include <utility>

namespace chesspp
{
    namespace config
    {
        class BoardConfig : public Configuration
        {
        public:
            using BoardSize_t = std::uint8_t;
            using CellSize_t = std::uint16_t;
        private:
            std::string layout_path, initial_layout;
            BoardSize_t board_width, board_height;
            CellSize_t cell_width, cell_height;

        public:
            BoardConfig()
            : Configuration("config.json")
            , layout_path(res_path + std::string(reader()["chesspp"]["board"]["initial_layout"]))
            , board_width                       (reader()["chesspp"]["board"]["width"]          )
            , board_height                      (reader()["chesspp"]["board"]["height"]         )
            , cell_width                        (reader()["chesspp"]["board"]["cell_width"]     )
            , cell_height                       (reader()["chesspp"]["board"]["cell_height"]    )
            {
                std::ifstream s {initial_layout};
                std::string layout ((std::istreambuf_iterator<char>(s)), std::istreambuf_iterator<char>());
                initial_layout = std::move(layout);
            }

            std::string initialLayout() const noexcept { return initial_layout; }
            BoardSize_t boardWidth   () const noexcept { return board_width;    }
            BoardSize_t boardHeight  () const noexcept { return board_height;   }
            CellSize_t  cellWidth    () const noexcept { return cell_width;     }
            CellSize_t  cellHeight   () const noexcept { return cell_height;    }
        };
    }
}

#endif
