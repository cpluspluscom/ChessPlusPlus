#include "BoardConfig.hpp"

namespace chesspp
{
    namespace config
    {
        BoardConfig::BoardConfig(GraphicsConfig const &gfx)
        : Configuration("config/board.json")
        , board_width  (reader()["chesspp"]["board"]["width"]      )
        , board_height (reader()["chesspp"]["board"]["height"]     )
        , cell_width   (reader()["chesspp"]["board"]["cell width"] )
        , cell_height  (reader()["chesspp"]["board"]["cell height"])
        {
            auto pieces = reader()["chesspp"]["board"]["pieces"];
            auto suits  = reader()["chesspp"]["board"]["suits"];
            for(BoardSize_t r = 0; r < board_height; ++r)
            {
                for(BoardSize_t c = 0; c < board_width; ++c)
                {
                    auto piece = pieces[r][c];
                    auto suit  = suits [r][c];
                    if(piece.type() != json_null) //it is OK if suit is null
                    {
                        layout[{c, r}] = std::make_pair<PieceClass_t, SuitClass_t>(piece, suit);
                    }
                }
            }

            auto const &tex = gfx.spritePaths("board", "pieces");
            for(auto const &suit : tex)
            {
                for(auto const &piece : suit.second.object())
                {
                    textures[suit.first][piece.first] = gfx.normalize(Textures_t::mapped_type::mapped_type(piece.second));
                }
            }
        }
    }
}

