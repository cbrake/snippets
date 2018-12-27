module Main exposing (Model, Msg(..), init, main, update, view)

import Browser
import Html exposing (Html, div, text)


main =
    Browser.sandbox { init = init, update = update, view = view }



-- MODEL


type alias Model =
    Int


compose f g x =
    f (g x)


textd : String -> Html msg
textd s =
    -- all of the following are equivalent
    -- text (Debug.log "text: " s)
    -- text <| Debug.log "text: " s
    Debug.log "text: " s |> text


init : Model
init =
    let
        a =
            10

        b =
            20

        _ =
            Debug.log "a+b" a + b
    in
    0



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
        [ textd "hello there!"
        ]
