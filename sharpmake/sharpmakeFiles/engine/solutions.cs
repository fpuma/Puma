namespace Puma
{
    [Sharpmake.Generate]
    class MiniEngineSolution : Puma.Common.IMySolution
    {
        public MiniEngineSolution()
            : base("MiniEngine")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);
            conf.AddProject<Puma.Engine>(target);
            conf.AddProject<Puma.EngineTest>(target);
        }
    }

    [Sharpmake.Generate]
    class ExternLibs : Puma.Common.IMySolution
    {
        public ExternLibs()
            : base("ExternLibs")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Extern.Box2D>(target);
        }
    }
}

