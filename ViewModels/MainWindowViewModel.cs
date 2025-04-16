namespace just_for_fun.ViewModels;


/*
public partial class MainWindowViewModel : ViewModelBase
{
    public string Greeting { get; } = "Welcome to Avalonia!";
}
*/

public class MainWindowViewModel : ViewModelBase
{
    public string Greeting => "Welcome to Avalonia! This is my added text.";
}