#include "ToucanEditor.h"
#include "App.h"

namespace Toucan {

ToucanEditor::ToucanEditor()
    : App("Toucan Editor")
{
}

ToucanEditor::~ToucanEditor()
{
}

} // namespace Toucan

int main()
{
    Toucan::ToucanEditor editor;
    editor.Run();
    return 0;
}