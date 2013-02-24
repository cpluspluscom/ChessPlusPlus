namepspace chesspp {
    Event::Event()
    {
    }

    Event::~Event()
    {
    }
    
    //pure virtual, do nothing
    void Event::OnClosed() {
    }
    void Event::OnResized(uint w, uint h) {
    }
    void Event::OnLostFocus() {
    }
    void Event::OnGainedFocus() {
    }
    void Event::OnTextEntered(sf::Uint32 unicode) {
    }
    void Event::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system) {
    }
    void Event::OnKeyReleased(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system) {
    }
    void Event::OnMouseWheelMoved(int delta, int x, int y) {
    }
    void Event::OnLButtonPressed(int x, int y) {
    }
    void Event::OnLButtonReleased(int x, int y) {
    }
    void Event::OnRButtonPressed(int x, int y) {
    }
    void Event::OnRButtonReleased(int x, int y) {
    }
    void Event::OnMButtonPressed(int x, int y) {
    }
    void Event::OnMButtonReleased(int x, int y) {
    }
    void Event::OnMouseButtonPressed(sf::Mouse::Button button, int x, int y) {
    }
    void Event::OnMouseButtonReleased(sf::Mouse::Button button, int x, int y) {
    }
    void Event::OnMouseMoved(int x, int y) {
    }
    void Event::OnMouseEnteredWindow() {
    }
    void Event::OnMouseLeftWindow() {
    }
    void Event::OnJoystickButtonPressed(uint joystickID, uint button) {
    }
    void Event::OnJoystickButtonReleased(uint joystickID, uint button) {
    }
    void Event::OnJoystickMoved(uint joystickID, sf::Joystick::Axis axis, float position) {
    }
    void Event::OnJoystickConnected(uint joystickID) {
    }
    void Event::OnJoystickDisconnected(uint joystickID) {
    } 
}