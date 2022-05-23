import logging
from gym.envs.registration import register

logger = logging.getLogger(__name__)

register(
    id='Multiagent-eval-3agents-v0',
    entry_point='custom_env_eval_3_agents.custom_env_test_eval_3_agents:MultiAgent',
)