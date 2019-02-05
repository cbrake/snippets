module Main exposing (Model, Msg(..), init, main, update, view)

import Browser
import ButtonWidget
import Html exposing (Html, button, div, h1, text)
import Html.Events exposing (onClick)


main =
    Browser.sandbox { init = init, update = update, view = view }



-- MODEL


type alias Model =
    { buttonState : ButtonWidget.Model }


init : Model
init =
    { button = Button.init
    }



-- UPDATE


type Msg
    = Increment
    | Decrement


update : Msg -> Model -> Model
update msg model =
    case msg of
        Increment ->
            model + 1

        Decrement ->
            model - 1



-- VIEW


view : Model -> Html Msg
view model =
    div []
        [ h1 [] [ text "elm button example" ]
        , button [ onClick Decrement ] [ text "-" ]
        , div [] [ text (String.fromInt model) ]
        , button [ onClick Increment ] [ text "+" ]
        ]
