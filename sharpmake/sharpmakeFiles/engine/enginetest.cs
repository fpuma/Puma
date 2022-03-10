namespace Puma
{
    [Sharpmake.Generate]
    class EngineTest : Puma.Common.IMyApplication
    {
        public EngineTest()
            : base("EngineTest", @"enginetest")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Puma.Engine>(target);

            conf.IncludePaths.Add(SourceRootPath);
            conf.IncludePaths.Add(Puma.Physics.SharedFilesPath);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}