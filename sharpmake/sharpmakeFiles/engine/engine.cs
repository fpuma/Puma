using Sharpmake;

namespace Puma
{
    [Sharpmake.Generate]
    class Engine : Puma.Common.IMyLib
    {
        public Engine()
            : base ("Engine", @"engine")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPrivateDependency<Puma.Nina>(target);
            conf.AddPrivateDependency<Puma.Leo>(target);
            conf.AddPublicDependency<Puma.Time>(target);
            conf.AddPublicDependency<Puma.Utils>(target);
            conf.AddPublicDependency<Puma.Logger>(target);

            conf.IncludePrivatePaths.Add(@"\private");
            conf.IncludePaths.Add(@"\public");

            conf.PrecompHeader = @"precompiledengine.h";
            conf.PrecompSource = @"precompiledengine.cpp";

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}
