namespace NotPseudo.Syntax
{
    public class AssignStatement : Node
    {
        public string Identifier { get; set; }
        public Node Expression { get; set; }
    }
}