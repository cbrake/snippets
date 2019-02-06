module Diagram exposing (Msg(..), view)

import Svg exposing (..)
import Svg.Attributes exposing (..)
import Svg.Events exposing (..)


type Msg
    = Button1
    | Button2


button : Int -> Int -> Msg -> Svg Msg
button xLoc yLoc clickMsg =
    rect
        [ x (String.fromInt xLoc)
        , y (String.fromInt yLoc)
        , rx "5"
        , width "40"
        , height "20"
        , fill "black"
        , onClick clickMsg
        ]
        []


view =
    svg [ width "120", height "120", viewBox "0 0 120 120" ]
        [ button 10 10 Button1
        , button 60 10 Button2
        ]
