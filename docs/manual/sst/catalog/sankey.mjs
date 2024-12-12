//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

globalThis.sst = globalThis.sst || {};

sst.sankey = function(edges, {
  showNodeWeights = false,
  getEdgeSource = (edge) => Array.isArray(edge) ? edge[0] : edge.source,
  getEdgeTarget = (edge) => Array.isArray(edge) ? edge[1] : edge.target,
  getEdgeWeight = (edge) => Array.isArray(edge) ? edge[2] : edge.weight,
  getNodeId = (node) => node,
  getNodeLabel = (nodeId, nodeInfo) =>
      nodeId + (showNodeWeights ? ` (${nodeInfo.weight})` : ""),
  getNodeLabelPadding = (nodeId, nodeInfo) => 5,
  nodes = [],
  getExplicitNodeLabel = getNodeLabel,
  getExplicitNodeLabelPadding = getNodeLabelPadding,
  width = 640,
  height = 480,
  marginLeft = 10,
  marginTop = 10,
  marginBottom = 10,
  marginRight = 10,
} = {}) {
  // Build the set of node IDs specified by the nodes array.
  const nodeNodeIds = new Set();
  for (const node of nodes) {
    nodeNodeIds.add(getNodeId(node));
  }

  // Build the set of node IDs specified by the edges array.
  const edgeNodeIds = new Set();
  for (const edge of edges) {
    edgeNodeIds.add(getEdgeSource(edge));
    edgeNodeIds.add(getEdgeTarget(edge));
  }

  // Build the full array of nodes in the format needed by D3.
  const d3Nodes = nodes.map(node => ({
                              id: getNodeId(node),
                              isImplicit: false,
                              originalNode: node,
                            }));
  for (const edgeNodeId of edgeNodeIds) {
    if (!nodeNodeIds.has(edgeNodeId)) {
      d3Nodes.push({
        id: edgeNodeId,
        isImplicit: true,
      });
    }
  }

  // Build the full array of edges in the format needed by D3.
  const d3Edges = edges.map(edge => ({
                              source: getEdgeSource(edge),
                              target: getEdgeTarget(edge),
                              value: getEdgeWeight(edge),
                              originalEdge: edge,
                            }));

  // Generate and add the diagram data to d3Nodes and d3Edges.
  d3.sankey().nodeId(node => node.id).nodeAlign(d3.sankeyLeft).extent([
    [marginLeft, marginTop],
    [width - marginRight, height - marginBottom],
  ])({nodes: d3Nodes, links: d3Edges});

  // Adjust the node property getters to work on d3Nodes.
  function nodeGetter(getNodeFoo, getExplicitNodeFoo) {
    return function(d3Node) {
      const nodeInfo = {
        weight: d3Node.value,
      };
      return d3Node.isImplicit ?
                 getNodeFoo(d3Node.id, nodeInfo) :
                 getExplicitNodeFoo(d3Node.originalNode, nodeInfo);
    };
  }
  getNodeLabel = nodeGetter(getNodeLabel, getExplicitNodeLabel);
  getNodeLabelPadding =
      nodeGetter(getNodeLabelPadding, getExplicitNodeLabelPadding);

  // Adjust the edge property getters to work on d3Edges.
  function edgeGetter(getEdgeFoo) {
    return function(d3Edge) {
      const edgeInfo = {};
      return getEdgeFoo(d3Edge.originalEdge, edgeInfo);
    };
  }
  getEdgeSource = edgeGetter(getEdgeSource);
  getEdgeTarget = edgeGetter(getEdgeTarget);
  getEdgeWeight = edgeGetter(getEdgeWeight);

  const svg = d3.create("svg")
                  .attr("width", width)
                  .attr("height", height)
                  .attr("viewBox", [0, 0, width, height]);

  svg.append("g")
      .selectAll("rect")
      .data(d3Nodes)
      .join("rect")
      .attr("x", node => node.x0)
      .attr("y", node => node.y0)
      .attr("width", node => node.x1 - node.x0)
      .attr("height", node => node.y1 - node.y0);

  svg.append("g")
      .attr("fill", "none")
      .selectAll("g")
      .data(d3Edges)
      .join("g")
      .style("mix-blend-mode", "multiply")
      .append("path")
      .attr("d", d3.sankeyLinkHorizontal())
      .attr("stroke", "lightgray")
      .attr("stroke-width", (edge) => Math.max(edge.width, 1));

  svg.append("g")
      .attr("font-family", "sans-serif")
      .attr("font-size", 16)
      .selectAll("text")
      .data(d3Nodes)
      .join("text")
      .attr("x",
            node => node.x0 < width / 2 ?
                        node.x1 + getNodeLabelPadding(node) :
                        node.x0 - getNodeLabelPadding(node))
      .attr("y", node => (node.y0 + node.y1) / 2)
      .attr("text-anchor",
            node => node.x0 < width / 2 ? "start" : "end")
      .text(node => getNodeLabel(node));

  return svg.node();
};
