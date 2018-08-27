# Lightning Network Graph Analysis

Analyse the lightning network graph to find articulation points

Uses `lncli describegraph` output, which is piped through
[lightning-network-graphxml](https://github.com/kulpreet/lightning-network-graphxml)
before being processed using BGL here.

## Metrics

For now we compute centrality, number of biconnected components and
the number of articulation points.

Results are meant to be published on a daily metrics page, which is
not built yet.
