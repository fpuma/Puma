namespace Puma
{
    [Sharpmake.Generate]
    class Physics : Puma.Common.IExternLib
    {
        public Physics()
            : base("Physics", @"physics2dmodule\source\physics")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPrivateDependency<Export.Box2D>(target);
            conf.AddPublicDependency<Puma.Utils>(target);

            conf.IncludePrivatePaths.Add(@"\private");
            conf.IncludePaths.Add(@"\public");

            conf.PrecompHeader = @"precompiledphysics.h";
            conf.PrecompSource = @"precompiledphysics.cpp";

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

            conf.SolutionFolder = "Modules";
        }
    }
}